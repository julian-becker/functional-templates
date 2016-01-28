//
//  custom_infix.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 07.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#pragma once

#include <functional>
#include <list>

template <typename BINARY_FUNCTION, typename = void>
struct make_infix_ext;

template <
    typename BINARY_FUNCTION
> struct
make_infix_ext<BINARY_FUNCTION> {
    private: struct
    delay {
        constexpr delay(typename std::add_rvalue_reference<typename BINARY_FUNCTION::first_argument_type>::type arg1)
        : arg1(std::forward<typename BINARY_FUNCTION::first_argument_type>(arg1)) {}
        
        constexpr delay(typename std::add_lvalue_reference<typename BINARY_FUNCTION::first_argument_type>::type arg1)
        : arg1(arg1) {}
        ~delay() {}
        typename BINARY_FUNCTION::first_argument_type arg1;
    };
    
    private: enum class
    OPERATOR{ auxiliary };
    
    public: static constexpr auto
    result = OPERATOR::auxiliary;
    
    public: friend constexpr delay
    operator < (
        typename BINARY_FUNCTION::first_argument_type arg1,
        const OPERATOR&)
    {
        return delay(arg1);
    }
    
    public: friend constexpr typename BINARY_FUNCTION::result_type
    operator > (
        const delay&& delayed,
        typename BINARY_FUNCTION::second_argument_type arg2)
    {
        return BINARY_FUNCTION()(delayed.arg1,arg2);
    }
};


struct
__plus : public std::binary_function<int,int,int> {
    constexpr int operator() (int a, int b) const {
        return a+b;
    }
};


static constexpr auto
PLUS = make_infix_ext<__plus>::result;



#include <vector>
#include <numeric>
struct
__up_to : public std::binary_function<int,int,std::vector<int>> {
    std::vector<int> operator() (int a, int b) const {
        const int s = b-a+1;
        std::vector<int> v(s>0? s : 0);
        std::iota (std::begin(v), std::end(v), a);
        return v;
    }
};

constexpr auto
UPTO = make_infix_ext<__up_to>::result;

struct __up{};
struct __to{};
constexpr auto UP = __up{};
constexpr auto TO = __to{};

constexpr auto operator - (const __up&, const __to&) {
    return UPTO;
}

struct
__down_to : public std::binary_function<int,int,std::vector<int>> {
    std::vector<int> operator() (int a, int b) const {
        int s = a-b+1;
        std::vector<int> v(s>0? s : 0);
        std::generate_n(std::begin(v), s, [&a](){ return a--; });
        return v;
    }
};

constexpr auto
DOWNTO = make_infix_ext<__down_to>::result;

struct __down{};
constexpr auto DOWN = __down{};

constexpr auto operator - (const __down&, const __to&) {
    return DOWNTO;
}

