//
//  init.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "init.h"

// for tests only:
#include <meta_assert.h>
#include <list/list.h>


using namespace
list;

ASSERT_EQUAL(init<list<int,double,wchar_t>>,list<int,double>);
ASSERT_EQUAL(init<list<int>>,list<>);
