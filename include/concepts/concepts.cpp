//
//  concepts.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#define ENABLE_TESTS
#include "concepts.h"

#include <concepts/BaseConcepts.h>
#include <list/list.h>
#include <meta_assert.h>

using namespace concepts;


template <typename T, typename = check<constrain<T,Signed>>> struct
test_concepts{};

template <typename T, typename = void> struct
test_concepts2;

template <typename T> struct
test_concepts2<T,check<constrain<T,Signed>>> {};



#include <thread>
void duitarenuidaetr(){
//    test_concepts<int> t;
    test_concepts2<signed> t2;
//    using tst = constrain_t<unsigned,Signed>;
//    using tp = check<constrain<unsigned,Signed>>;
    using sgn = constrain_t<signed int, Signed>;
    using cpyconst = constrain<unsigned, CopyConstructible>;
    static_assert(cpyconst::value,"err");
}