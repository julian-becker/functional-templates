//
//  tail.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__tail__
#define __FunctionalTemplates__tail__

#include <result_of.h>

namespace list {

    namespace __dtl {
        template <typename LIST> struct
        __tail;
        
        template <template <typename...> class LIST_TYPE, typename T, typename...TS> struct
        __tail<LIST_TYPE<T,TS...>> {
            using result = LIST_TYPE<TS...>;
        };
    
    }
    
    template <typename LIST> using tail = result_of<__dtl::__tail<LIST>>;
}

#endif /* defined(__FunctionalTemplates__tail__) */
