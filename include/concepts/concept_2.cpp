//
//  concept_signed.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 27.05.16.
//  Copyright © 2016 Julian Becker. All rights reserved.
//

#include "concept_signed.hpp"
#include <type_traits>
#include <functional>
#include <future>
#include <iostream>


template <typename T, template <typename...> class Concept, typename = Concept<T>> struct
concept_assert {};


template <template <typename...> class Concept> struct
c_both {
    template <typename T1, typename T2, typename = Concept<T1>, bool = std::is_same<T1,T2>::value> struct
    concept_impl;

    template <typename T1, typename T2, typename CommonConcept> struct
    concept_impl<T1,T2,CommonConcept,true> : CommonConcept {};
    
    template <typename T1, typename T2> struct
    concept : concept_impl<T1,T2> {};
};


template <typename T, typename Continuation1=T> struct
c_monoid;



template <typename BinOp, typename = void>
struct make_infix_ext;

template <
    typename BinOp
> struct
make_infix_ext<BinOp> {

    private: template <typename T> struct
    delay {
        T arg1;
    };
    
    public: static constexpr enum class
    Operator{ } result { };
    
    public: template <typename T> friend
    constexpr auto
    operator < (T&& arg1, const Operator&) {
        return delay<std::decay_t<T>>{ std::forward<T>(arg1) };
    }
    
    public: template <typename T, typename U> friend
    constexpr auto
    operator > (delay<T>&& delayed, U&& arg2)
    {
        return BinOp{}(std::move(delayed.arg1), std::forward<U>(arg2));
    }
};






/// concept of signedness:
template <typename T> struct
c_signed;
// {
//     static bool is_negative(const T&);
//     static T negate(const T&);
// };

template <typename Signed, typename concept = c_signed<Signed>>
Signed operator - (const Signed& value) {
    return concept::negate(value);
}

template <typename T> struct
c_signed_primitive {
    static bool is_negative(T val) {
        return val<(T)0;
    }
    static T negate(T i) {
        return -i;
    }
};

template <> struct
c_signed<char> : c_signed_primitive<char> {};

template <> struct
c_signed<short> : c_signed_primitive<short> {};

template <> struct
c_signed<int> : c_signed_primitive<int> {};

template <> struct
c_signed<long> : c_signed_primitive<long> {};

template <> struct
c_signed<float> : c_signed_primitive<float> {};

template <> struct
c_signed<double> : c_signed_primitive<double> {};







/// ###########################################
/// ## MONOID
/// ###########################################


struct
__plus_monoid {
    template <
        typename T,
        typename U,
        typename concept = c_both<c_monoid>::concept<std::decay_t<T>, std::decay_t<U>>
    >
    auto operator() (T&& a, U&& b) const {
        return concept::append(std::forward<T>(a),std::forward<U>(b));
    }
};

static constexpr auto
PLUS = make_infix_ext<__plus_monoid>::result;


template <typename T> struct
c_monoid_integral {
    constexpr static T neutral() { return (T)0; }
    static T append(T i, T j) {
        return i + j;
    }
};

template <> struct
c_monoid<char> : c_monoid_integral<char> {};

template <> struct
c_monoid<short> : c_monoid_integral<short> {};

template <> struct
c_monoid<int> : c_monoid_integral<int> {};

template <> struct
c_monoid<long> : c_monoid_integral<long> {};


template <typename T> struct
c_monoid<std::future<T>> {
    constexpr static std::future<T> neutral() {
        std::promise<T> p;
        p.set_value(c_monoid<T>::neutral());
        return p.get_future();
    }
    
    constexpr static std::future<T> append(std::future<T> a, std::future<T> b) {
        return std::async(std::bind([](std::future<T>& a, std::future<T>& b){
            return c_monoid<T>::append(a.get(),b.get());
        }, std::move(a), std::move(b)));
    }
};


struct
my_signed_type {
    int val;
};

template <> struct
c_signed<my_signed_type> {
    static bool is_negative(const my_signed_type l) {
        return l.val<0L;
    }
    static my_signed_type negate(const my_signed_type& l) {
        return my_signed_type{ -l.val };
    }
};

template <> struct
c_monoid<my_signed_type> {
    static constexpr my_signed_type neutral{ 0 };
    static my_signed_type append(const my_signed_type& a, const my_signed_type& b) {
        return my_signed_type{ a.val + b.val };
    }
};

constexpr my_signed_type c_monoid<my_signed_type>::neutral;


void test_concepts() {
    my_signed_type i{ -5 }, j{};
    auto z = i <PLUS> j;
    auto a = std::async([]{ return my_signed_type{4}; });
    auto b = std::async([]{ return my_signed_type{7}; });
    auto c = std::move(a) <PLUS> std::move(b);
    std::cout << "got: " << c.get().val << std::endl;
    c_both<c_monoid>::concept<int,int> test;
}

