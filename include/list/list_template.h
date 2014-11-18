//
//  list_template.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__list_template__
#define __FunctionalTemplates__list_template__

#include <result_of.h>

namespace list {

    // ! @cond Doxygen_Suppress
    namespace __dtl {
        template <typename LIST> struct
        __list_template;
        
        template <template <typename...> class LIST_TEMPLATE, typename...TS> struct
        __list_template<LIST_TEMPLATE<TS...>> {
            template <typename...ELEMENTS> using result = LIST_TEMPLATE<ELEMENTS...>;
        };
    }
    // ! @endcond
    
    template <typename LIST> using
    list_template = result_of<__dtl::__list_template<LIST>>;
}

#endif /* defined(__FunctionalTemplates__list_template__) */
