//
//  init.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__init__
#define __FunctionalTemplates__init__

#include <result_of.h>
#include <list/head.h>
#include <list/tail.h>
#include <list/cons.h>

// for tests only:
#include <meta_assert.h>
#include <list/list.h>


namespace list {
    // ! @cond Doxygen_Suppress
    namespace __dtl {
        template <typename LIST> struct
        __init {
            using result = cons<
                               head<LIST>,
                               result_of<__init<tail<LIST>>>
                           >;
        };
        
        template <typename T, template <typename...> class LIST_TYPE> struct
        __init<LIST_TYPE<T>> {
            using result = LIST_TYPE<>;
        };
    }
    // ! @endcond
    
    template <typename LIST> using
    init = result_of<__dtl::__init<LIST>>;
    
    ASSERT_EQUAL(init<list<int,double,wchar_t>>,list<int,double>);
    ASSERT_EQUAL(init<list<int>>,list<>);
}
#endif /* defined(__FunctionalTemplates__init__) */
