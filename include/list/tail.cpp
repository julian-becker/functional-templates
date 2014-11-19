//
//  tail.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "tail.h"

// for testing purposes:
#include <meta_assert.h>
#include <list/list.h>

using namespace
list;

ASSERT_EQUAL(tail<list<void*,char,double>>,list<char,double>);
