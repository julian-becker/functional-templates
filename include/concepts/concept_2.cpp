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
#include <vector>
#include <list>
#include <map>
#include <utility>


#define REQUIRES typename =

namespace __dtl {
    template <typename T, template <typename> class Concept>
    auto __models(Concept<T>) -> std::true_type;

    template <typename T, template <typename> class Concept>
    auto __models(...) -> std::false_type;
}

template <typename T, template <typename> class Concept> using
req_models = std::enable_if_t<decltype(__dtl::__models<T,Concept>({}))::value>;

template <typename T, typename U> using
req_equals = std::enable_if_t<std::is_same<T,U>::value>;



template <typename BinOp> struct
make_infix_ext {

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
    
    public: template <
        typename T, typename U
    > friend
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

template <typename T, REQUIRES req_models<std::decay_t<T>,c_signed>>
auto operator - (T&& value) {
    return c_signed<std::decay_t<T>>::negate(std::forward<T>(value));
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


struct
__plus_monoid {
    template <
        typename T,
        typename U,
        REQUIRES req_models<std::decay_t<T>, c_monoid>,
        REQUIRES req_models<std::decay_t<U>, c_monoid>,
        REQUIRES req_equals<std::decay_t<T>,std::decay_t<U>>
    >
    auto operator() (T&& a, U&& b) const {
        return c_monoid<std::decay_t<T>>::append(std::forward<T>(a),std::forward<U>(b));
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



template <typename Iterable> struct
c_monoid_iterable {
    constexpr static Iterable neutral() {
        return Iterable{};
    }
    
    template <typename T, typename U, REQUIRES req_equals<std::decay_t<T>, std::decay_t<U>>>
    constexpr static auto append(T&& a, U&& b) {
        using std::begin;
        using std::end;
        Iterable result{};
        std::copy(begin(a), end(a), std::back_inserter(result));
        std::copy(begin(b), end(b), std::back_inserter(result));
        return result;
    }
};

template <typename T> struct
c_monoid<std::list<T>> : c_monoid_iterable<std::list<T>> {};

template <typename T> struct
c_monoid<std::vector<T>> : c_monoid_iterable<std::vector<T>> {};

template <typename T, typename U> struct
c_monoid<std::map<T,U>> : c_monoid_iterable<std::map<T,U>> {};





template <typename T> struct
c_ostreamable;

template <typename Iterable> struct
c_ostreamable_iterable {
    template <typename Iterable1, REQUIRES req_equals<std::decay_t<Iterable1>,Iterable>>
    static std::ostream& writeTo(std::ostream& ostr, Iterable1&& val) {
        using std::begin;
        using std::end;
        auto it = begin(val);
        ostr << "{";
        c_ostreamable<typename Iterable::value_type>::writeTo(ostr,*it++);
        
        if(it != val.end())
            ostr << ", ";
        
        for(;it != end(val);) {
            c_ostreamable<typename Iterable::value_type>::writeTo(ostr,*it++);
            if(it == val.end())
                break;
            ostr << ", ";
        }
        ostr << "}";
        return ostr;
    }
};

template <typename T> struct
c_ostreamable<std::vector<T>> : c_ostreamable_iterable<std::vector<T>> {};

template <typename T> struct
c_ostreamable<std::list<T>> : c_ostreamable_iterable<std::list<T>> {};

template <typename T, typename U> struct
c_ostreamable<std::map<T,U>> : c_ostreamable_iterable<std::map<T,U>> {};

template <typename T, typename U> struct
c_ostreamable<std::pair<T,U>> {
    template <typename V, REQUIRES req_equals<std::decay_t<V>,std::pair<T,U>>>
    static std::ostream& writeTo(std::ostream& ostr, V&& val) {
        c_ostreamable<std::decay_t<T>>::writeTo(ostr, val.first);
        ostr << ": ";
        c_ostreamable<std::decay_t<U>>::writeTo(ostr, val.second);
        return ostr;
    }
};

template <typename T> struct
c_ostreamable_builtin {
    template <typename U, REQUIRES req_equals<std::decay_t<U>,T>>
    static std::ostream& writeTo(std::ostream& ostr, U&& val) {
        return ostr << std::forward<U>(val);
    }
};

template <> struct
c_ostreamable<char> {
    template <typename U, REQUIRES req_equals<std::decay_t<U>,char>>
    static std::ostream& writeTo(std::ostream& ostr, U&& val) {
        return ostr << int{std::forward<U>(val)};
    }
};

template <> struct
c_ostreamable<short> : c_ostreamable_builtin<short> {};

template <> struct
c_ostreamable<int> : c_ostreamable_builtin<int> {};

template <> struct
c_ostreamable<long> : c_ostreamable_builtin<long> {};

template <typename T, REQUIRES req_models<std::decay_t<T>, c_ostreamable>>
std::ostream& operator << (std::ostream& ostr, T&& v) {
    return c_ostreamable<std::decay_t<T>>::writeTo(ostr, std::forward<T>(v));
}




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






struct no_monoid {} n;

void test_concepts() {
    my_signed_type i{ -5 }, j{};
    auto z = i <PLUS> j;
    auto a = std::async([]{ return my_signed_type{4}; });
    auto b = std::async([]{ return my_signed_type{7}; });
    auto c = std::async([]{ return my_signed_type{111}; });
    auto d = std::move(a) <PLUS> std::move(b) <PLUS> std::move(c);
    std::cout << "got: " << c.get().val << std::endl;
    std::vector<int> result = std::vector<int>{ 1,2,3 } <PLUS> std::vector<int>{ 3, 4, 4 };
    std::list<int> l1{ 1,2,3 }, l2{ 3, 4, 4 };
    std::list<int> result1 = l1 <PLUS> l2;
    std::map<char,std::list<std::pair<int,int>>> m{ {1,{{4,55}}}, {4, std::list<std::pair<int,int>>{{6,7},{122,123},{8,9},{98,99}}} };
    
    std::cout << m << std::endl;
    std::cout << result1 << std::endl;
}

