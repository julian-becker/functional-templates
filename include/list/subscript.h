//
//  subscript.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__subscript__
#define __FunctionalTemplates__subscript__

#include <result_of.h>
#include <list/head.h>
#include <list/tail.h>
#include <meta_types/meta_types.h>

// for testing purposes only
#include <meta_assert.h>
#include <list/list.h>

namespace list {
    // ! @cond Doxygen_Suppress
    namespace __dtl {
        template <typename INDEX,typename LIST> struct
        __subscript;
        
        template <typename INDEX_TYPE,INDEX_TYPE INDEX,typename LIST> struct
        __subscript<meta_types::value_type<INDEX_TYPE,INDEX>,LIST> {
            using result = result_of<__subscript<meta_types::value_type<INDEX_TYPE,INDEX-1>,tail<LIST>>>;
        };
        
        template <typename INDEX_TYPE,typename LIST> struct
        __subscript<meta_types::value_type<INDEX_TYPE,static_cast<INDEX_TYPE>(0)>,LIST> {
            using result = head<LIST>;
        };

    }
    // ! @endcond
    
    template <typename INDEX,typename LIST> using
    subscript = result_of<__dtl::__subscript<INDEX, LIST>>;
    
    ASSERT_EQUAL(subscript<meta_types::int_<0>,list<void*,int*,wchar_t,float>>,void*);
    ASSERT_EQUAL(subscript<meta_types::int_<1>,list<void*,int*,wchar_t,float>>,int*);
}

#endif /* defined(__FunctionalTemplates__subscript__) */
