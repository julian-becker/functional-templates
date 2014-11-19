//
//  dtl_tail.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__tail__
#   error "this file should never be included directly"
#endif

namespace
list {

    namespace
    __dtl {
    
        template <typename LIST> struct
        __tail;
        
        template <
            template <typename...> class
            LIST_TYPE,
        
            typename
            T,
        
            typename...
            TS
        > struct
        __tail<LIST_TYPE<T,TS...>> {
            using result = LIST_TYPE<TS...>;
        };
    }
}

