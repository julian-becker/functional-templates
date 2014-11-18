//
//  head.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__head__
#define __FunctionalTemplates__head__

#include <result_of.h>


namespace list {
    
    namespace __dtl {
        template <typename LIST> struct
        __head;
        
        template <template <typename...> class LIST_TYPE, typename T, typename...TS> struct
        __head<LIST_TYPE<T,TS...>> {
            using result = T;
        };
    
    }
    
    template <typename LIST> using head = result_of<__dtl::__head<LIST>>;

}


#endif /* defined(__FunctionalTemplates__head__) */
