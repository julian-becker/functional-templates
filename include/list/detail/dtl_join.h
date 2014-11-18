//
//  dtl_join.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__join__
#   error "this file should never be included directly"
#endif

#include <result_of.h>

namespace list {
  
    //! @cond Doxygen_Suppress
    namespace __dtl {
    // ! 
        template <typename LIST1,typename LIST2> struct
        __join;
        
        template <template <typename...> class LIST_TEMPLATE, typename...ELEMENTS1, typename...ELEMENTS2> struct
        __join<LIST_TEMPLATE<ELEMENTS1...>,LIST_TEMPLATE<ELEMENTS2...>> {
            using result = LIST_TEMPLATE<ELEMENTS1...,ELEMENTS2...>;
        };
    }
    //! @endcond Doxygen_Suppress

}
