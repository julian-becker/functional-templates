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
    /// general list
    template <typename...> struct list;
    
    /// non-empty list specialization
    template <typename HEAD,typename...TAIL> struct
    list<HEAD,TAIL...> {
        
        /// the first element in the list
        public: using
        head = HEAD;
        
        /// the rest of the list
        public: using
        tail = list<TAIL...>;
    };
}

#endif /* defined(__FunctionalTemplates__list__) */
