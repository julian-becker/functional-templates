//
//  join_n.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 27.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "join_n.h"

#include <meta_assert.h>
#include <list/list.h>

using namespace list;

ASSERT_EQUAL(join_n<list<void*,int>,list<char,double>>,list<void*,int,char,double>);
ASSERT_EQUAL(join_n<list<void*,int>,list<char,double>,list<>>,list<void*,int,char,double>);
ASSERT_EQUAL(join_n<list<void*,int>,list<char,double>,list<>,list<float>>,list<void*,int,char,double,float>);
