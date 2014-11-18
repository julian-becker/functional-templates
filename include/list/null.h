//
//  null.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__null__
#define __FunctionalTemplates__null__

#include <list/clear.h>
#include <logic.h>
#include <equal.h>
#include <conditional.h>

// for tests only:
#include <meta_assert.h>
#include <list/list.h>


namespace list {

    template <typename LIST> using
    null = if_true<equal<LIST,clear<LIST>>,TRUE,FALSE>;
    
    ASSERT_NOT(null<list<int,double,wchar_t>>);
    ASSERT(null<list<>>);
}

#endif /* defined(__FunctionalTemplates__null__) */
