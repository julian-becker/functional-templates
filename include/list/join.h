//
//  join.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__join__
#define __FunctionalTemplates__join__

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
    
    
    /// @brief metafunction JOIN.
    /// @tparam LIST1 the first list
    /// @tparam LIST2 the second list, based on the same list template as LIST1.
    /// @returns a new list that is the concatenation of the types in LIST1 and LIST2
    template <typename LIST1, typename LIST2> using
    join = result_of<__dtl::__join<LIST1,LIST2> >;

}

#endif /* defined(__FunctionalTemplates__join__) */
