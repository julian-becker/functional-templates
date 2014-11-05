//
//  curry.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 05.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#pragma once
#include <functional>

namespace __dtl {

    template <typename FUNCTION> struct
    __curry;


    template <typename R,typename T> struct
    __curry<std::function<R(T)>> {
        using type = std::function<R(T)>;
        const type function;
        __curry(const type fun) : function(fun) {}
        
        type transform () const { return function; }
    };

    template <typename R,typename T,typename...Ts> struct
    __curry<std::function<R(T,Ts...)>> {
        using remaining_type = typename __curry<std::function<R(Ts...)> >::type;
        using type = std::function<remaining_type(T)>;
        const std::function<remaining_type(T)> function;
        __curry(const std::function<R(T,Ts...)>& fun)
        : function(
            [=](const T& t) {
                return __curry<std::function<R(Ts...)>>([=](const Ts&...ts){ return fun(t, ts...); }).transform();
            }
        ) {}
        type transform () const {
            return function;
        }
    };
}

template <typename R,typename...Ts>
auto curry(const std::function<R(Ts...)>& fun) -> decltype(__dtl::__curry<std::function<R(Ts...)>>(fun).transform()) {
    return __dtl::__curry<std::function<R(Ts...)>>(fun).transform();
}

template <typename R,typename...Ts>
auto curry(R(*fun)(Ts...)) -> decltype(__dtl::__curry<std::function<R(Ts...)>>(fun).transform()) {
    return __dtl::__curry<std::function<R(Ts...)>>(fun).transform();
}
