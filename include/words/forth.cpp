//
//  forth.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 27.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#include "forth.h"

#include <demangle.h>
#include <iostream>

using namespace words;

template <typename T> void
show() {
    std::cout << demangle<T>() << std::endl;
}


void forth_test() {
    using resT = eval_t<word<quote<dup>,quote<>,cons>>;
    show<resT>();

    using resT2 = eval_t<word<int_<42>,succ,succ,pred,succ > >;
    show<resT2>();

    using resT3 = eval_t<word<int_<2>,pred,pred,null > >;
    show<resT3>();

    using resT4 = eval_t<word<quote<bool_<true>>,quote<int_<1337>,dup>,quote<int_<31>>,ifte > >;
    show<resT4>();

    using resT5 = eval_t<word<int_<0>,quote<null>,quote<succ>,quote<dup,pred,multiply>,ifte>>;
    show<resT5>();

    using resT6 = eval_t<word<int_<6>,fac>>; // -> stack<value_type<int,720>>
    show<resT6>();
    
    using resT7 = eval_t<word<int_<3>,int_<7>,quote<int_<11>,multiply>,app2>>;
    show<resT7>();
    
    using resT8 = eval_t<word<int_<2>,small>>;
    show<resT8>();
    
    using resT9 = eval_t<word<int_<1>,fib>>;
    show<resT9>();
    
    using resT10 = eval_t<word<int_<6>,fib>>;
    show<resT10>();
    
}