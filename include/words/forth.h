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
    template <typename WORD, typename STACK> using
    apply_to = typename WORD::template apply<STACK>;
    
    template <typename T,typename...WORDS> using
    continuation_of = typename T::template continuation<WORDS...>;
    
    /// @brief: This will be equal to the stack resulting from executing WORD and REMAINING_WORDS
    ///         with the stack STACK as input
    template <typename STACK, typename WORD, typename...REMAINING_WORDS> using
    do_continuation_ext = continuation_of<apply_to<WORD,STACK>,REMAINING_WORDS...>;
  
    struct
    id {
        template<typename STACK> struct
        apply {
            template<typename...> struct
            continuation : STACK {};
     
            template<typename WORD, typename... REST> struct
            continuation<WORD, REST...> : do_continuation_ext<STACK,WORD,REST...> {};
        };
    };

    template <typename STACK, typename...REMAINING_WORDS> using
    do_continuation = do_continuation_ext<STACK, id, REMAINING_WORDS...>;

    template<typename... WORDS> struct
    word {
        template<typename STACK> struct
        apply {
            template<typename... REST> using
            continuation = do_continuation< do_continuation<STACK,WORDS...>, REST...>;
        };
    };

    /// @brief: pushes the given argument onto the stack when executed:
    /// push<A,B,C> == A B C
    template <typename...TS> struct
    push {
        template<typename STACK> struct
        apply {
            using newStack = typename STACK::template push<TS...>;
            template<typename... REST> using
            continuation = words::do_continuation<newStack,REST...>;
        };
    };
   
    /// will push a word onto the stack:
    /// quote<A,B> == [ A B ]
    template <typename...TS> struct
    quote : push<word<TS...>> {};
/*        template<typename STACK> struct
        apply {
            template<typename... REST> struct
            continuation {
                using stack = do_continuation<typename STACK::template push<word<TS...>>, REST...>;
            };
        };
    };*/

    /// executes the word on top of the stack:
    /// [A] i == A
    struct
    i {
        template<typename STACK> struct
        apply {
            template<typename... REST> using
            continuation = do_continuation<typename STACK::pop, typename STACK::top, REST...>;
        };
    };

    /// [B] [A] cake == [[B] A] [A [B]]
    struct
    cake {
        template<typename STACK> struct
        apply {
            using quotedA = push<typename STACK::top>;
            using quotedB = push<typename STACK::pop::top>;
            using newStack = typename STACK::pop::pop::
                                template push<
                                    word<quotedB,quotedA,i>,
                                    word<quotedA,i,quotedB>
                                >;
            template<typename... REST> using
            continuation = do_continuation<newStack, REST...>;
        };
    };
    
    /// [B] [A] k == A
    struct
    k {
        template<typename STACK> struct
        apply {
            using wordA = typename STACK::top;
            using newStack = typename STACK::pop::pop;
            
            template<typename... REST> using
            continuation = do_continuation<newStack,wordA,REST...>;
        };
    };

    template<typename WORD, typename STACK = words::stack<>> using
    eval_t = typename do_continuation<STACK,WORD>::stack;
    
    template <bool B> struct
    bool_ : push<meta_types::bool_<B>> {};

    template <int N> struct
    int_ : push<meta_types::int_<N>> {};
    
    
    /// int_<N> succ == int_<N+1>
    struct
    succ {
        template<typename STACK> struct
        apply {
            using top = typename STACK::top;
            using newStack = typename STACK::pop::template push<meta_types::int_<top::value+1>>;
            
            template<typename... REST> using
            continuation = do_continuation<newStack,REST...>;
        };
    };

    /// int_<N> pred == int_<N-1>
    struct
    pred {
        template<typename STACK> struct
        apply {
            using top = typename STACK::top;
            using newStack = typename STACK::pop::template push<meta_types::int_<top::value-1>>;
            
            template<typename... REST> using
            continuation = do_continuation<newStack,REST...>;
        };
    };
    
    /// int_<0> null == true
    /// int_<N> null == false
    struct
    null {
        template<typename STACK> struct
        apply {
            using top = typename STACK::top;
            using newStack = typename STACK::pop::template push<meta_types::bool_<top::value==0>>;
            
            template<typename... REST> using
            continuation = do_continuation<newStack,REST...>;
        };
    };
    
    /// int_<A> int_<B> multiply == int_<A*B>
    struct
    multiply {
        template<typename STACK> struct
        apply {
            using A = typename STACK::top;
            using B = typename STACK::pop::top;
            using newStack = typename STACK::pop::pop::template push<meta_types::int_<A::value*B::value>>;
            
            template<typename... REST> using
            continuation = do_continuation<newStack,REST...>;
        };
    };
    
    /// int_<A> int_<B> add == int_<A+B>
    struct
    add {
        template<typename STACK> struct
        apply {
            using A = typename STACK::top;
            using B = typename STACK::pop::top;
            using newStack = typename STACK::pop::pop::template push<meta_types::int_<A::value+B::value>>;
            
            template<typename... REST> using
            continuation = do_continuation<newStack,REST...>;
        };
    };
    
    /// int_<N> negate == int_<-N>
    struct
    negate {
        template<typename STACK> struct
        apply {
            using A = typename STACK::top;
            using newStack = typename STACK::pop::template push<meta_types::int_<-A::value>>;
            
            template<typename... REST> using
            continuation = do_continuation<newStack,REST...>;
        };
    };
    
    /// [true]  [iftrue] [else] pred == iftrue
    /// [false] [iftrue] [else] pred == else
    struct
    ifte {
        template<typename STACK> struct
        apply {
            using elsequot = typename STACK::top;
            using ifquot = typename STACK::pop::top;
            constexpr static bool test = eval_t<typename STACK::pop::pop::top,typename STACK::pop::pop::pop>::top::value;
            using newStack = typename STACK::pop::pop::pop;
            using execute = std::conditional_t<test, ifquot, elsequot>;
            
            template<typename... REST> using
            continuation = do_continuation<newStack,execute,REST...>;
        };
    };
    
    
    /// [A] zap  ==
    struct zap : word<quote<>,k> {};
    
    /// [B] [A] dip == A [B]
    struct dip : word<cake,k> {};
    
    /// [B] [A] cons == [[B] A]
    struct cons : word<cake,quote<>,k> {};
    
    /// [A] i == A
    ///  using i = word<quote<quote<>>,dip,k> {}; // already defined as primitive
    
    /// [A] dup == [A] [A]
    struct dup : word<quote<>,cake,dip,dip> {};
    
    /// [A] unit == [[A]]
    struct unit : word<quote<>,cons> {};
    
    /// [B] [A] swap == [A] [B]
    struct swap : word<unit,dip> {};
    
    /// [B] [A] w == [B] [B] A
    struct w : word<quote<dup>,dip,i> {};
    
    /// [B] [A] over == [B] [A] [B]
    struct over : word<quote<>,cons,w,quote<>,cons,dip> {};
    
    /// [B] [A] nip == [A]
    struct nip : word<swap,zap> {};
    
    /// [B] [A] cat == [B A]
    struct cat : word<quote<quote<i>,dip,i>,cons,cons> {}; /// something wrong??
    
    /// int_<N> fac == int_<N!>
    struct fac;
    struct fac : word<quote<null>,quote<succ>,quote<dup,pred,fac,multiply>,ifte> {};
    
    /// [x] [y] [A] [B] app2 == [x A] [y B]
    struct app2 : word<dup,dip,dip> {};
    
    /// int_<1> small == bool_<true>
    /// int_<0> small == bool_<true>
    /// int_<N> small == bool_<false> // N>1 or N<0
    struct small : word<quote<int_<-1>,add,null>,quote<zap,bool_<true>>,quote<null>,ifte> {};
    
    struct fib;
    struct fib : word<quote<small>,quote<>,quote<pred,dup,pred,quote<fib>,app2,add>,ifte> {};
}

void forth_test();

//! @endcond Doxygen_Suppress

#endif /* defined(__FunctionalTemplates__forth__) */
