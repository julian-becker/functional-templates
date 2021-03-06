//
//  curry.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 05.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#pragma once
#include <functional>
#include <type_traits>
#include <callable/callable.h>

namespace __dtl {

    template <typename FUNCTION> struct
    __curry;


    // ! @cond Doxygen_Suppress
    
    // specialization for functions with a single argument
    template <typename R,typename T> struct
    __curry<std::function<R(T)>> {
        using
        type = std::function<R(T)>;
        
        const type
        result;
        
        __curry(type fun) : result(fun) {}
        
    };

    // recursive specialization for functions with more arguments
    template <typename R,typename T,typename...Ts> struct
    __curry<std::function<R(T,Ts...)>> {
        using
        remaining_type = typename __curry<std::function<R(Ts...)> >::type;
        
        using
        type = std::function<remaining_type(T)>;
        
        const type
        result;
        
        __curry(std::function<R(T,Ts...)> fun)
        : result (
            [=](const T& t) {
                return __curry<std::function<R(Ts...)>>([=](const Ts&...ts){ return fun(t, ts...); }).result;
            }
        ) {}
    };
    
    
    // auxiliary class used to wrap a naked lambda argument which cannot
    // otherwise matched against an std::function<R(Ts...)>
    template <typename T> struct
    __wrapper {
        using
        type = T;
    };
    
    // ! @endcond
}

template <typename CALLABLE> auto
curry(CALLABLE callable)
-> typename __dtl::__curry<typename callable::callable_traits<CALLABLE>::wrapper_type>::type
{
    return __dtl::__curry<typename callable::callable_traits<CALLABLE>::wrapper_type>(callable).result;
}

void test_curry();