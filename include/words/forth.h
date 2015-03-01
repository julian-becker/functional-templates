//
//  forth.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 27.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//  Note: this code was inspired by https://pubby8.wordpress.com/2012/10/15/stack-based-template-metaprogramming-in-c-11/

#ifndef __FunctionalTemplates__forth__
#define __FunctionalTemplates__forth__

#include <words/stack.h>
#include <type_traits>
#include <meta_types/meta_types.h>

//! @cond Doxygen_Suppress

namespace
words {

    template <typename T> using
    stack_of = typename T::stack;
    
    template <typename WORD, typename STACK> using
    apply_to = typename WORD::template apply<STACK>;
    
    template <typename T,typename...WORDS> using
    continuation_of = typename T::template continuation<WORDS...>;
    
    /// @brief: This will be equal to the stack resulting from executing WORD and REMAINING_WORDS
    ///         with the stack STACK as input
    template <typename STACK, typename WORD, typename...REMAINING_WORDS> using
    do_continuation_ext = stack_of<continuation_of<apply_to<WORD,STACK>,REMAINING_WORDS...>>;
  
    struct
    id {
        template<typename STACK> struct
        apply {
            template<typename...> struct
            continuation {
                using
                stack = STACK;
            };
     
            template<typename WORD, typename... REST> struct
            continuation<WORD, REST...> {
                using
                stack = do_continuation_ext<STACK,WORD,REST...>;
            };
      };
    };

    template <typename STACK, typename...REMAINING_WORDS> using
    do_continuation = do_continuation_ext<STACK, id, REMAINING_WORDS...>;

    template<typename... WORDS> struct
    word {
        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
                using
                stack = do_continuation< do_continuation<STACK,WORDS...>, REST...>;
            };
        };
    };

    /// @brief: pushes the given argument onto the stack when executed:
    /// push<A,B,C> == A B C
    template <typename...TS> struct
    push {
        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
                using newStack = typename STACK::template push<TS...>;
                using stack = do_continuation<newStack,REST...>;
            };
        };
    };
   
    /// will push a word onto the stack:
    /// quote<A,B> == [ A B ]
    template <typename...TS> struct
    quote {
        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
                using stack = do_continuation<typename STACK::template push<word<TS...>>, REST...>;
            };
        };
    };

    /// executes the word on top of the stack:
    /// [A] i == A
    struct
    i {
        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
                using stack = do_continuation<typename STACK::pop, typename STACK::top, REST...>;
            };
        };
    };

    /// [B] [A] cake == [[B] A] [A [B]]
    struct
    cake {
        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
                using quotedA = push<typename STACK::top>;
                using quotedB = push<typename STACK::pop::top>;
                using newStack = typename STACK::pop::pop::
                                    template push<
                                        word<quotedB,quotedA,i>,
                                        word<quotedA,i,quotedB>
                                    >;
                using stack = do_continuation<newStack, REST...>;
            };
        };
    };
    
    /// [B] [A] k == A
    struct
    k {
        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
                using wordA = typename STACK::top;
                using newStack = typename STACK::pop::pop;
                using stack = do_continuation<newStack,wordA,REST...>;
            };
        };
    };
    
    struct zap : word<quote<>,k> {};
    struct dip : word<cake,k> {};
    struct cons : word<cake,quote<>,k> {};
    //  using i = word<quote<quote<>>,dip,k> {}; // already defined as primitive
    struct dup : word<quote<>,cake,dip,dip> {};
    
    template<typename WORD, typename STACK = words::stack<>> using
    eval_t = typename do_continuation<STACK,WORD>::stack;
}

void forth_test();

//! @endcond Doxygen_Suppress

#endif /* defined(__FunctionalTemplates__forth__) */
