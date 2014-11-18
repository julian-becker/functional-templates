//
//  reverse.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__reverse__
#define __FunctionalTemplates__reverse__

#include <result_of.h>
#include <list/head.h>
#include <list/cons.h>
#include <list/tail.h>
#include <list/clear.h>

// for testing purposes only
#include <meta_assert.h>
#include <list/list.h>

namespace list {
    // ! @cond Doxygen_Suppress
    namespace __dtl {
        template <typename LIST_REMAINING,typename LIST_REVERSED> struct
        __reverse {
            using result = result_of<
                               __reverse<
                                   tail<LIST_REMAINING>,
                                   cons<
                                       head<LIST_REMAINING>,
                                       LIST_REVERSED
                                   >
                               >
                            >;
        };
        
        template <template <typename...> class LIST_TYPE,typename LIST_REVERSED> struct
        __reverse<LIST_TYPE<>,LIST_REVERSED> {
            using result = LIST_REVERSED;
        };

    }
    // ! @endcond
    
    template <typename LIST> using
    reverse = result_of<__dtl::__reverse<LIST,clear<LIST>>>;
    
    ASSERT_EQUAL(reverse<list<void*,int*,wchar_t,float>>,list<float,wchar_t,int*,void*>);
}


#endif /* defined(__FunctionalTemplates__reverse__) */
