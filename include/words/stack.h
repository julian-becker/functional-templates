//
//  stack.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 27.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__stack__
#define __FunctionalTemplates__stack__

namespace
words {
    template <typename ...ELMS > struct
    stack;
    
    template <> struct
    stack<> {
        public: template <typename...NEW_ELMS> using
        push = stack<NEW_ELMS...>;
    };
    
    template <typename HEAD, typename ...ELMS > struct
    stack<HEAD,ELMS...> {
        public: template <typename...NEW_ELMS> using
        push = stack<NEW_ELMS...,HEAD,ELMS...>;
        
        public: using
        top = HEAD;
        
        public: using
        pop = stack<ELMS...>;
    };
    
};

#endif /* defined(__FunctionalTemplates__stack__) */
