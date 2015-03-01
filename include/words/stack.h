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

    //! @cond Doxygen_Suppress
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
    //! @endcond Doxygen_Suppress
    
    
    /// @brief: A template metaprogramming stack
    ///         Do not provide the template arguments directly, instead use
    ///            stack<>::push< T1, T2, T3>
    ///         which will first push T1, then T2 and finally T3 onto the stack.
    template <typename ...> struct
    stack;
    
    /// @brief: The specialization of the empty stack
    template <> struct
    stack<> {
        /// @brief: push any number of items onto the stack.
        ///         The items NEW_ELMS will be pushed in the order listed
        public: template <typename...NEW_ELMS> using
        push = result_of<__dtl::push_impl<stack<>, NEW_ELMS...>>;
    };
    
    /// @brief: Specialization for the non-empty stack that supports 'pop' and 'top'.
    template <typename HEAD, typename ...ELMS > struct
    stack<HEAD,ELMS...> {

        /// @brief: push any number of items onto the stack.
        ///         The items NEW_ELMS will be pushed in the order listed
        public: template <typename...NEW_ELMS> using
        push = result_of<__dtl::push_impl<stack<HEAD,ELMS...>, NEW_ELMS...>>;
        
        /// @brief: Get the top element of the stack.
        public: using
        top = HEAD;
        
        /// @brief: Drops the top element of the stack.
        public: using
        pop = stack<ELMS...>;
    };
    
    ASSERT_EQUAL(stack<>::push<int>::push<char>::push<double>,stack<>::push<int,char,double>);
    
};

#endif /* defined(__FunctionalTemplates__stack__) */
