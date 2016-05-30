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
#include <sstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
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

template <typename T, typename U> using
req_compatible = std::enable_if_t<std::is_same<std::decay_t<T>,std::decay_t<U>>::value>;


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



/// ###########################################
/// ## MONOID
/// ###########################################



struct __plus_tag{};
struct __times_tag{};

template <typename T, typename Tag = __plus_tag> struct
c_monoid;

template <typename T, typename TAG> struct
c_monoid_builtin;

template <typename T> struct
c_monoid_builtin<T,__plus_tag> {
    constexpr static T neutral() { return (T)0; }
    static T append(T i, T j) {
        return std::move(i) + std::move(j);
    }
};

template <typename T> struct
c_monoid_builtin<T,__times_tag> {
    constexpr static T neutral() { return (T)0; }
    static T append(T i, T j) {
        return i * j;
    }
};

struct
__plus_monoid {
    template <typename T, typename U>
    auto operator() (T&& a, U&& b) const {
        return c_monoid<std::common_type_t<std::decay_t<T>,std::decay_t<U>>, __plus_tag>::append(std::forward<T>(a),std::forward<U>(b));
    }
};

struct
__times_monoid {
    template <typename T, typename U>
    auto operator() (T&& a, U&& b) const {
        return c_monoid<std::common_type_t<std::decay_t<T>,std::decay_t<U>>, __times_tag>::append(std::forward<T>(a),std::forward<U>(b));
    }
};

// left associative
static constexpr auto
PLUS = make_infix_ext<__plus_monoid>::result;

// left associative
static constexpr auto
TIMES = make_infix_ext<__times_monoid>::result;

#define MONOID_BUILTIN_IMPL(T,TAG) \
    template <> struct \
    c_monoid<T,TAG> : c_monoid_builtin<T,TAG> {}

MONOID_BUILTIN_IMPL(char,__times_tag);
MONOID_BUILTIN_IMPL(char,__plus_tag);
MONOID_BUILTIN_IMPL(unsigned char,__times_tag);
MONOID_BUILTIN_IMPL(unsigned char,__plus_tag);
MONOID_BUILTIN_IMPL(short,__times_tag);
MONOID_BUILTIN_IMPL(short,__plus_tag);
MONOID_BUILTIN_IMPL(unsigned short,__times_tag);
MONOID_BUILTIN_IMPL(unsigned short,__plus_tag);
MONOID_BUILTIN_IMPL(int,__times_tag);
MONOID_BUILTIN_IMPL(int,__plus_tag);
MONOID_BUILTIN_IMPL(unsigned int,__times_tag);
MONOID_BUILTIN_IMPL(unsigned int,__plus_tag);
MONOID_BUILTIN_IMPL(long,__times_tag);
MONOID_BUILTIN_IMPL(long,__plus_tag);
MONOID_BUILTIN_IMPL(unsigned long,__times_tag);
MONOID_BUILTIN_IMPL(unsigned long,__plus_tag);
MONOID_BUILTIN_IMPL(std::string,__plus_tag);


template <typename T> struct
c_monoid_builtin_back_insertable {
    constexpr static T neutral() { return {}; }
    template <typename U, typename V>
    static T append(U&& a, V&& b) {
        T result(a);
        std::copy(b.begin(), b.end(), std::back_inserter(result));
        return result;
    }
};

template <typename T> struct
c_monoid_builtin_insertable {
    constexpr static T neutral() { return {}; }
    template <typename U, typename V>
    static T append(U&& a, V&& b) {
        T result(a);
        std::copy(b.begin(), b.end(), std::inserter(result,result.end()));
        return result;
    }
};

template <typename T> struct
c_monoid<std::vector<T>,__plus_tag> : c_monoid_builtin_back_insertable<std::vector<T>> {};

template <typename T> struct
c_monoid<std::list<T>,__plus_tag> : c_monoid_builtin_back_insertable<std::list<T>> {};

template <typename T, typename U> struct
c_monoid<std::map<T, U>,__plus_tag> : c_monoid_builtin_insertable<std::map<T,U>> {};

template <typename T, typename U> struct
c_monoid<std::multimap<T, U>,__plus_tag> : c_monoid_builtin_insertable<std::multimap<T,U>> {};

template <typename T, typename U> struct
c_monoid<std::unordered_map<T, U>,__plus_tag> : c_monoid_builtin_insertable<std::unordered_map<T,U>> {};

template <typename T> struct
c_monoid<std::set<T>,__plus_tag> : c_monoid_builtin_insertable<std::set<T>> {};

template <typename T> struct
c_monoid<std::multiset<T>,__plus_tag> : c_monoid_builtin_insertable<std::multiset<T>> {};

template <typename T> struct
c_monoid<std::unordered_set<T>,__plus_tag> : c_monoid_builtin_insertable<std::unordered_set<T>> {};



//class Functor f where
//  fmap :: (a -> b) -> f a -> f b
template <typename T> struct
c_functor;

template <typename T> struct
c_functor<std::list<T>> {
    template <typename Fn>
    static auto fmap(Fn&& f) {
        return std::bind([](Fn& f, const std::list<T>& a){
            std::list<decltype(f(std::declval<T>()))> result;
            std::transform(a.begin(), a.end(), std::back_inserter(result), f);
            return result;
        }, std::forward<Fn>(f), std::placeholders::_1);
    }
};


struct
__functor_fmap {
    template <typename T, typename U>
    auto operator() (T&& a, U&& b) const {
        return c_functor<std::decay_t<U>>::fmap(std::forward<T>(a))(std::forward<U>(b));
    }
};

// left associative
static constexpr auto
FMAP = make_infix_ext<__functor_fmap>::result;


struct no_monoid {} n;

void test_concepts() {
    auto z1 = 1 <PLUS> 2 <PLUS> 6;
    auto z2 = 2 <TIMES> 5;
    auto z3 = std::string("hello") <PLUS> " world!";
    auto z4 = std::vector<int>{ 1, 2, 3 } <PLUS> std::vector<int>{ 4, 5, 6, 7 };
    auto z5 = std::set<int>{ 1,2,3 } <PLUS> std::set<int>{ 1, 4, 6 };
    auto z6 = std::unordered_set<int>{ 1,2,3 } <PLUS> std::unordered_set<int>{ 1, 4, 6 };
    auto z7 = std::unordered_map<int,int>{ {1, 100}, {2, 200}, {3, 300} } <PLUS> std::unordered_map<int,int>{ {1, 100}, {4, 400}, {6, 600} };
    auto z8 = std::multiset<int>{ 1,2,3 } <PLUS> std::multiset<int>{ 1, 4, 6 };
    auto z9 = std::map<int,int>{ {1, 100}, {2, 200}, {3, 300} } <PLUS> std::map<int,int>{ {1, 100}, {4, 400}, {6, 600} };
    auto z10= std::multimap<int,int>{ {1, 100}, {2, 200}, {3, 300} } <PLUS> std::multimap<int,int>{ {1, 100}, {4, 400}, {6, 600} };
    std::cout << "z3 = " << z3 << std::endl;
    auto toString = [](int i){ return (std::ostringstream{} << i).str(); };
    auto z11 = toString <FMAP> std::list<int>{ 1, 3, 4, 5, 6, 7 };
    for(const auto&x : z11) std::cout << x << std::endl;
}

