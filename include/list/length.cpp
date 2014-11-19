//
//  length.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "length.h"
// for tests only:
#include <meta_assert.h>
#include <list/list.h>
#include <fold.h>

using namespace list;
using namespace meta_types;

ASSERT_EQUAL(length<list<int,double,wchar_t>>,uint_<3>);
ASSERT_EQUAL(length<list<>>,uint_<0>);