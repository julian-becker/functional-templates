//
//  dtl_head.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__head__
#   error "this file should never be included directly"
#endif

namespace list {
    
    //! @cond Doxygen_Suppress
    namespace __dtl {
        template <typename LIST> struct
        __head;
        
        template <template <typename...> class LIST_TYPE, typename T, typename...TS> struct
        __head<LIST_TYPE<T,TS...>> {
            using result = T;
        };
    
    }
    //! @endcond
}

