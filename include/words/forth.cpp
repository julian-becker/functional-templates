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
}