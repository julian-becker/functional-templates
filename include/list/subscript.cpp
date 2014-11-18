//
//  subscript.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "subscript.h"

// for testing purposes only
#include <meta_assert.h>
#include <list/list.h>
#include <meta_types/meta_types.h>

using namespace
list;
    
ASSERT_EQUAL(subscript<meta_types::int_<0>,list<void*,int*,wchar_t,float>>,void*);
ASSERT_EQUAL(subscript<meta_types::int_<1>,list<void*,int*,wchar_t,float>>,int*);

