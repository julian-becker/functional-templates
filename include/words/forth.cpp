//
//  forth.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 27.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#include "forth.h"

#include <cxxabi.h>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace words;

template <typename T>
std::string demangle() {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status),
        std::free
    };
    return (status==0) ? res.get() : typeid(T).name() ;
}

template <typename T> void
show() {
    std::cout << demangle<T>() << std::endl;
}


void forth_test() {
    using resT = eval_t<word<quote<dup>,quote<>,cons>>;
    show<resT>();
}