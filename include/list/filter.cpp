//
//  filter.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "filter.h"

#include <type_traits>
#include <logic.h>
#include <fold.h>
#include <conditional.h>
#include <meta_assert.h>
#include <list.h>
#include <append.h>

    
using namespace list;

template <typename T> using
is_integral = typename std::conditional<std::is_integral<T>::value,TRUE,FALSE>::type;

ASSERT_EQUAL(is_integral<int>,TRUE);
ASSERT_EQUAL(is_integral<double>,FALSE);
ASSERT_EQUAL(if_true< is_integral<int>,
                cons<int,list<>>,
                list<>>,list<int>);

ASSERT_EQUAL(filter<is_integral,list<double>>,
             list<>);
ASSERT_EQUAL(filter<is_integral,list<double,int,float,long>>,
             list<int,long>);
