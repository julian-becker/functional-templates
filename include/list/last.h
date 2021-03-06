//
//  last.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__last__
#define __FunctionalTemplates__last__

#include <result_of.h>
#include <list/tail.h>
#include <meta_assert.h>

// for tests only:
#include <list/list.h>


namespace list {
    // ! @cond Doxygen_Suppress
    namespace __dtl {
        template <typename LIST> struct
        __last {
            using result = result_of<__last<tail<LIST>>>;
        };
        
        template <typename T, template <typename...> class LIST_TYPE> struct
        __last<LIST_TYPE<T>> {
            using result = T;
        };
    }
    // ! @endcond
    
    template <typename LIST> using
    last = result_of<__dtl::__last<LIST>>;
    
    ASSERT_EQUAL(last<list<int,double,wchar_t>>,wchar_t);
    ASSERT_EQUAL(last<list<int>>,int);
}

#endif /* defined(__FunctionalTemplates__last__) */
