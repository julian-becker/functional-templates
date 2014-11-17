//
//  append.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__append__
#define __FunctionalTemplates__append__

#include <result_of.h>

namespace prelude {
  namespace list {
  
    //! @cond Doxygen_Suppress
    namespace __dtl {
    // ! 
        template <typename LIST1,typename LIST2> struct
        __append;
        
        template <template <typename...> class LIST_TEMPLATE, typename...ELEMENTS1, typename...ELEMENTS2> struct
        __append<LIST_TEMPLATE<ELEMENTS1...>,LIST_TEMPLATE<ELEMENTS2...>> {
            using result = LIST_TEMPLATE<ELEMENTS1...,ELEMENTS2...>;
        };
    }
    //! @endcond Doxygen_Suppress
    
    
    /// @brief metafunction APPEND.
    /// @tparam LIST1 the first list
    /// @tparam LIST2 the second list, based on the same list template as LIST1.
    /// @returns a new list that is the concatenation of the types in LIST1 and LIST2
    template <typename LIST1, typename LIST2> using
    append = result_of<__dtl::__append<LIST1,LIST2> >;

  }
}

#endif /* defined(__FunctionalTemplates__append__) */
