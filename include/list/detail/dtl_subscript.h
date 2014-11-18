//
//  dtl_subscript.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__subscript__
#   error "this file should never be included directly"
#endif

#include <result_of.h>
#include <list/head.h>
#include <list/tail.h>
#include <meta_types/meta_types.h>

namespace list {

    // ! @cond Doxygen_Suppress
    namespace __dtl {
        template <typename INDEX,typename LIST> struct
        __subscript {
            using result = result_of<__subscript<meta_types::dec<INDEX>,tail<LIST>>>;
        };
        
        template <typename INDEX_TYPE,typename LIST> struct
        __subscript<meta_types::value_type<INDEX_TYPE,static_cast<INDEX_TYPE>(0)>,LIST> {
            using result = head<LIST>;
        };

    }
    // ! @endcond

}

