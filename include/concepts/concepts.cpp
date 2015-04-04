//
//  concepts.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#define ENABLE_TESTS
#include "concepts.h"

#include <concepts/CopyConstructible.h>
#include <concepts/Signed.h>
#include <list/list.h>
#include <meta_assert.h>

using namespace concepts;

ASSERT_EQUAL(get_type<constrain<int,Signed>>::type,int);
ASSERT_EQUAL(get_type<constrain<constrain<int,Signed>>>::type,int);
ASSERT_EQUAL(get_constraints<constrain<constrain<int,Signed>,CopyConstructible>>::type,list::list<CopyConstructible,Signed>);
ASSERT(constrain<constrain<signed int, Signed>,Signed>);

#include <thread>
void duitarenuidaetr(){
    using sgn = constrain_t<signed int, Signed>;
    using cpyconst = constrain<unsigned, CopyConstructible>;
    static_assert(cpyconst::value,"err");
}