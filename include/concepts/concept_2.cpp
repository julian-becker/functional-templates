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

template <template <typename> class Concept> struct
c_both {
    template <typename T1, typename T2, typename = Concept<T1>, typename = Concept<T2>> struct
    concept_impl{};
    
    template <typename T1, typename T2> struct
    concept : concept_impl<T1,T2> {};
};


template <typename> struct
c_monoid;



template <typename BinOp, template <typename,typename> class Concept, typename = void>
struct make_infix_ext;

template <
    typename BinOp,
    template <typename,typename> class Concept
> struct
make_infix_ext<BinOp, Concept> {

    private: template <typename T> struct
    delay {
        T arg1;
    };
    
    private: enum class
    Operator{ auxiliary };
    
    public: static constexpr auto
    result = Operator::auxiliary;
    
    public: template <typename T> friend
    constexpr delay<T>
    operator < (T&& arg1, const Operator&) {
        return delay<T>{ std::forward<T>(arg1) };
    }
    
    public: template <typename T, typename U, typename = Concept<T, U>> friend
    constexpr U
    operator > (const delay<T>&& delayed, U arg2)
    {
        return BinOp{}(std::move(delayed.arg1), arg2);
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
template <typename T> struct
c_monoid;
// {
//      static T append(const T& a, const T& b) { return a <plus> b; }
//      static constexpr T neutral = (T)0;
// };

template <typename Monoid, typename concept = c_monoid<Monoid>>
Monoid operator + (const Monoid& a, const Monoid& b) {
    return concept::append(a,b);
}

struct
__plus_monoid {
    template <typename T, typename concept = c_monoid<T>>
    constexpr T operator() (const T& a, const T& b) const {
        return concept::append(a,b);
    }
};

static constexpr auto
PLUS = make_infix_ext<__plus_monoid, c_both<c_monoid>::concept>::result;


template <typename T> struct
c_monoid_integral {
    constexpr static T neutral = (T)0;
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
    j = -i;
    int t = -5, r, s;
    i = i + j;
    i = i + c_monoid<my_signed_type>::neutral;
    auto y = 5 <PLUS> 7.7;
    auto z = i <PLUS> j;
}

