//
//  forth.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 27.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__forth__
#define __FunctionalTemplates__forth__

#include <words/stack.h>
#include <type_traits>

//! @cond Doxygen_Suppress

namespace
words {

    template <typename T> using
    stack_of = typename T::stack;
    
    template <typename WORD, typename STACK> using
    apply_to = typename WORD::template apply<STACK>;
    
    template <typename T,typename...WORDS> using
    continuation_of = typename T::template continuation<WORDS...>;
    
    
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
                stack =stack_of<continuation_of<apply_to<WORD,STACK>,REST...>>;
            };
      };
    };

    template<typename... WORDS> struct
    word {
        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
            
            using
            stack = stack_of<
                        continuation_of<apply_to<id,
                            stack_of<continuation_of<apply_to<id,STACK>,WORDS...>
                            >
                        >,
                        REST...>
                    >;
            };
        };
    };
    

    template <typename WORD> struct
    unquote;

    template <typename WORD> struct
    unquote<word<WORD>> {
        using type = WORD;
    };

    
    template <typename WORD> using
    unquote_t = typename unquote<WORD>::type;
    
    

    struct
    k {
        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
                using quotedA = typename STACK::top;
                using quotedB = typename STACK::pop::top;
                using A = unquote_t<quotedA>;
                using newStack = typename STACK::pop::pop;
                using stack = stack_of<continuation_of<apply_to<A,newStack>,REST...>>;
            };
        };
    };
    
    struct
    s {
        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
                using quotedX = typename STACK::top;
                using quotedA = typename STACK::pop::top;
                using quotedB = typename STACK::pop::pop::top;
                using quotedC = typename STACK::pop::pop::pop::top;
                using X = unquote_t<quotedX>;
                using A = unquote_t<quotedA>;
                using B = unquote_t<quotedB>;
                using newStack = typename STACK::pop::pop::pop::template push<word<quotedC,B>>;
                using contX = continuation_of<apply_to<X,newStack>,REST...>;
                using newStack2 = typename stack_of<contX>::template push<quotedC>;
                using stack = stack_of<continuation_of<apply_to<A,newStack2>,REST...>>;
            };
        };
    };

    struct
    dup {
        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
                using tos = typename STACK::top;
                using newStack = typename STACK::template push<tos>;
                using stack = stack_of<continuation_of<apply_to<id,newStack>,REST...>>;
            };
        };
    };
    
    
    template<typename WORD, typename STACK = words::stack<>> struct
    eval {
        //using
        //stack = stack_of<continuation_of<apply_to<id,STACK>,WORD>>;
        using stack =  typename id::apply<STACK>::template continuation<WORD>::stack;
        
    };

    template<typename WORD, typename STACK = words::stack<>> using
    eval_t = typename eval<WORD,STACK>::stack;
    
    static_assert(std::is_same<
        stack<>,
        typename apply_to<id,stack<>>::continuation<>::stack
    >::value,"");
    
    static_assert(std::is_same<
        stack<id,id>,
        typename dup::apply<stack<id>>::template continuation<>::stack
    >::value,"");

    static_assert(std::is_same<
        stack<id>,
        eval_t<word<id>,stack<id>>
    >::value,"");

    int test();
    static_assert(std::is_same<int,decltype((test()))>::value,"error");
}

//! @endcond Doxygen_Suppress

#endif /* defined(__FunctionalTemplates__forth__) */
