//
//  Signed.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#define ENABLE_TESTS

#include "Signed.h"
#include <meta_assert.h>

using namespace concepts;

ASSERT(Signed::apply<char>);
ASSERT(Signed::apply<short>);
ASSERT(Signed::apply<int>);
ASSERT(Signed::apply<long>);
ASSERT(Signed::apply<float>);
ASSERT(Signed::apply<double>);
ASSERT_NOT(Signed::apply<unsigned char>);
ASSERT_NOT(Signed::apply<unsigned short>);
ASSERT_NOT(Signed::apply<unsigned int>);
ASSERT_NOT(Signed::apply<unsigned long>);
ASSERT_NOT(Signed::apply<unsigned long long>);
