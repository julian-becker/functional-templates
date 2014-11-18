//
//  reverse.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "reverse.h"

// for testing purposes only
#include <meta_assert.h>
#include <list/list.h>

using namespace
list;

ASSERT_EQUAL(reverse<list<void*,int*,wchar_t,float>>,list<float,wchar_t,int*,void*>);
