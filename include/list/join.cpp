//
//  join.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "join.h"

#include <meta_assert.h>
#include <list/list.h>

using namespace list;
    
ASSERT_EQUAL(join<list<void*,int>,list<char,double>>,list<void*,int,char,double>);
