//
//  cons.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__cons__
#define __FunctionalTemplates__cons__

#include <result_of.h>

namespace list {
    namespace __dtl {
        template <typename T,typename LIST> struct
        __cons;
        
        template <template <typename...> class LIST_TYPE, typename T, typename...TS> struct
        __cons<T,LIST_TYPE<TS...>> {
            using result = LIST_TYPE<T,TS...>;
        };
    
    }

    template <typename T, typename LIST> using
    cons = result_of<__dtl::__cons<T,LIST>>;
}

#endif /* defined(__FunctionalTemplates__cons__) */
