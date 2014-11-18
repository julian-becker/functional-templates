//
//  clear.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__clear__
#define __FunctionalTemplates__clear__

#include <result_of.h>

namespace list {

    namespace __dtl {
        template <typename LIST> struct
        __clear;
        
        template <template <typename...> class LIST_TYPE, typename...TS> struct
        __clear<LIST_TYPE<TS...>> {
            using result = LIST_TYPE<>;
        };
    
    }
    
    template <typename LIST> using clear = result_of<__dtl::__clear<LIST>>;
    
}

#endif /* defined(__FunctionalTemplates__clear__) */
