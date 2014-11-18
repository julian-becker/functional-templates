//
//  list.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__list__
#define __FunctionalTemplates__list__

#include <result_of.h>


namespace list {
    template <typename...> struct list {};
    
    namespace __dtl {
        template <typename LIST> struct
        __head;
        
        template <template <typename...> class LIST_TYPE, typename T, typename...TS> struct
        __head<LIST_TYPE<T,TS...>> {
            using result = T;
        };
    
    }
    
    template <typename LIST> using head = result_of<__dtl::__head<LIST>>;



    namespace __dtl {
        template <typename LIST> struct
        __tail;
        
        template <template <typename...> class LIST_TYPE, typename T, typename...TS> struct
        __tail<LIST_TYPE<T,TS...>> {
            using result = LIST_TYPE<TS...>;
        };
    
    }
    
    template <typename LIST> using tail = result_of<__dtl::__tail<LIST>>;



    namespace __dtl {
        template <typename LIST> struct
        __clear;
        
        template <template <typename...> class LIST_TYPE, typename...TS> struct
        __clear<LIST_TYPE<TS...>> {
            using result = LIST_TYPE<>;
        };
    
    }
    
    template <typename LIST> using clear = result_of<__dtl::__clear<LIST>>;
    
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

#endif /* defined(__FunctionalTemplates__list__) */
