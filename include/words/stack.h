//
//  stack.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 27.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__stack__
#define __FunctionalTemplates__stack__

#include <list/reverse.h>
#include <meta_assert.h>

namespace
words {

    namespace
    __dtl {
        template <typename STACK, typename...NEW_ELMS> struct
        push_impl;
        
        template <typename STACK> struct
        push_impl<STACK> {
            using result = STACK;
        };
        
        template <template <typename...TS> class STACK_T, typename NEW_HEAD, typename...NEW_ELMS, typename...ELMS> struct
        push_impl<STACK_T<ELMS...>,NEW_HEAD,NEW_ELMS...> {
            using result = typename push_impl<STACK_T<NEW_HEAD,ELMS...>,NEW_ELMS...>::result;
        };
    }
    
    template <typename ...ELMS > struct
    stack;
    
    template <> struct
    stack<> {
        public: template <typename...NEW_ELMS> using
        push = result_of<__dtl::push_impl<stack<>, NEW_ELMS...>>;
    };
    
    template <typename HEAD, typename ...ELMS > struct
    stack<HEAD,ELMS...> {

        public: template <typename...NEW_ELMS> using
        push = result_of<__dtl::push_impl<stack<HEAD,ELMS...>, NEW_ELMS...>>;
        
        public: using
        top = HEAD;
        
        public: using
        pop = stack<ELMS...>;
    };
    
    ASSERT_EQUAL(stack<>::push<int>::push<char>::push<double>,stack<>::push<int,char,double>);
    
};

#endif /* defined(__FunctionalTemplates__stack__) */
