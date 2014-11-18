//
//  dtl_filter.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__filter__
#   error "this file must never be included directly"
#endif

#include <conditional.h>
#include <append.h>


namespace list {
  
    //! @cond Doxygen_Suppress
    namespace __dtl {
    
        using namespace list;
        
        template <template <typename> class PREDICATE_FN> struct
        __helper {
            template <typename LIST, typename T> using
            cons_if =
                if_true< PREDICATE_FN<T>,
                    append<T,LIST>,
                    LIST>;
        };
        
    }
    //! @endcond Doxygen_Suppress
    
}
