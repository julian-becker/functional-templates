//
//  logic.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 06.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__logic__
#define __FunctionalTemplates__logic__

#if defined (ENABLE_TESTS)
#define ASSERT(...) static_assert(__VA_ARGS__::value,#__VA_ARGS__)
#else
#define ASSERT(...) 
#endif

#define ASSERT_NOT(...) ASSERT(!__VA_ARGS__)

// ###################################################################################

/// compile-time boolean
struct
TRUE {
    /// conversion to concrete boolean type:
    static constexpr bool
    value = true;
};

ASSERT(TRUE);

/// compile-time boolean
struct FALSE {
    /// conversion to concrete boolean type:
    static constexpr bool
    value = false;
};

ASSERT(!FALSE);

// ###################################################################################

/// extracts the resulting TRUE or FALSE from T::result
template <typename T> using
result_of = typename T::result;

//template <typename T> bool
//value_of = T::value;

// ###################################################################################

///! @cond Doxygen_Suppress
namespace __dtl {

    /// negates the given BOOL
    template <typename BOOL> struct
    __negate {
        /// if BOOL is anything but TRUE, result is TRUE
        using
        result = TRUE;
    };

    /// specialization of negate for TRUE, resulting in FALSE
    template <> struct
    __negate<TRUE> {
        /// yield FALSE only if argument is TRUE
        using
        result = FALSE;
    };
}
///! @endcond Doxygen_Suppress

template <typename BOOL> using
negate = result_of<__dtl::__negate<BOOL>>;

ASSERT(negate<FALSE>);
ASSERT_NOT(negate<TRUE>);
ASSERT(negate<negate<TRUE>>);
ASSERT_NOT(negate<negate<FALSE>>);

// ###################################################################################

///! @cond Doxygen_Suppress
namespace __dtl {

    template <typename BOOL,typename IF_TRUE,typename ELSE> struct
    __if_true {
        using
        result = ELSE;
    };

    template <typename IF_TRUE,typename ELSE> struct
    __if_true<TRUE,IF_TRUE,ELSE> {
        using
        result = IF_TRUE;
    };
}
///! @endcond Doxygen_Suppress

template <typename BOOL,typename IF_TRUE,typename ELSE>
using if_true = result_of<__dtl::__if_true<BOOL,IF_TRUE,ELSE>>;

ASSERT(if_true<TRUE,TRUE,FALSE>);
ASSERT_NOT(if_true<FALSE,TRUE,FALSE>);
ASSERT(if_true<FALSE,FALSE,TRUE>);
ASSERT_NOT(if_true<TRUE,FALSE,TRUE>);

// ###################################################################################

template <typename BOOL, typename IF_TRUE, typename ELSE> using
if_false = negate<if_true<BOOL, IF_TRUE, ELSE>>;

ASSERT_NOT(if_false<TRUE,TRUE,FALSE>);
ASSERT(if_false<FALSE,TRUE,FALSE>);
ASSERT_NOT(if_false<FALSE,FALSE,TRUE>);
ASSERT(if_false<TRUE,FALSE,TRUE>);

// ###################################################################################

///! @cond Doxygen_Suppress
namespace __dtl {

    template <typename BOOL1, typename BOOL2> struct
    __equal {
        using
        result = FALSE;
    };

    template <typename BOOL> struct
    __equal <BOOL,BOOL> {
        using
        result = TRUE;
    };
}
///! @endcond Doxygen_Suppress

template <typename BOOL1,typename BOOL2> using
equal = result_of<__dtl::__equal<BOOL1,BOOL2>>;

ASSERT(equal<TRUE,TRUE>);
ASSERT_NOT(equal<TRUE,FALSE>);
ASSERT_NOT(equal<FALSE,TRUE>);
ASSERT(equal<FALSE,FALSE>);

// ###################################################################################

///! @cond Doxygen_Suppress
namespace __dtl {

    template <template <typename,typename> class META_FUN, typename INIT, typename...TS> struct
    __foldr;

    template <template <typename,typename> class META_FUN, typename INIT, typename T, typename...TS> struct
    __foldr<META_FUN,INIT,T,TS...> {
        using
        result = META_FUN<T,result_of<__foldr<META_FUN,INIT,TS...>>>;
    };


    template <template <typename,typename> class META_FUN, typename INIT> struct
    __foldr<META_FUN,INIT> {
        using
        result = INIT;
    };
}
///! @endcond Doxygen_Suppress

template <template <typename,typename> class META_FUN, typename INIT, typename T, typename...TS> using
foldr = result_of<__dtl::__foldr<META_FUN, INIT, T, TS...>>;

// ###################################################################################

///! @cond Doxygen_Suppress
namespace __dtl {

    template <template <typename,typename> class META_FUN, typename INIT, typename...TS> struct
    __foldl;

    template <template <typename,typename> class META_FUN, typename INIT, typename T, typename...TS> struct
    __foldl<META_FUN,INIT,T,TS...> {
        using
        result = result_of<__foldl<META_FUN, META_FUN<INIT,TS...>>>;
    };


    template <template <typename,typename> class META_FUN, typename INIT> struct
    __foldl<META_FUN,INIT> {
        using
        result = INIT;
    };
}
///! @endcond Doxygen_Suppress

template <template <typename,typename> class META_FUN, typename INIT, typename T, typename...TS> using
foldl = result_of<__dtl::__foldl<META_FUN, INIT, T, TS...>>;

// ###################################################################################

///! @cond Doxygen_Suppress
namespace __dtl {

    template <typename BOOL1, typename BOOL2> struct
    __either {
        using
        result = TRUE;
    };

    template <> struct
    __either<FALSE,FALSE> {
        using
        result = FALSE;
    };
}
///! @endcond Doxygen_Suppress

template <typename BOOL1, typename BOOL2> using
either = result_of<__dtl::__either<BOOL1,BOOL2>>;

ASSERT(either<TRUE,TRUE>);
ASSERT(either<TRUE,FALSE>);
ASSERT(either<FALSE,TRUE>);
ASSERT_NOT(either<FALSE,FALSE>);

// ###################################################################################

///! @cond Doxygen_Suppress
namespace __dtl {
    
    template <typename BOOL1, typename BOOL2> struct
    __both {
        using
        result = FALSE;
    };

    template <> struct
    __both<TRUE,TRUE> {
        using
        result = TRUE;
    };
}
///! @endcond Doxygen_Suppress

template <typename BOOL1, typename BOOL2> using
both = result_of<__dtl::__both<BOOL1,BOOL2>>;

ASSERT(both<TRUE,TRUE>);
ASSERT(!both<FALSE,TRUE>);
ASSERT(!both<TRUE,FALSE>);
ASSERT(!both<FALSE,FALSE>);


// ###################################################################################

template <typename...BOOLS> using
any = foldr<either,FALSE,BOOLS...>;

// ###################################################################################

template <typename...BOOLS> using
all = foldr<both,TRUE,BOOLS...>;

// ###################################################################################

template <typename...BOOLS> using
none = negate<all<BOOLS...>>;

// ###################################################################################

ASSERT(all<TRUE>);
ASSERT(negate<all<FALSE>>);
ASSERT(negate<all<FALSE,TRUE,TRUE>>);

ASSERT(any<TRUE>);
ASSERT(any<TRUE,FALSE,TRUE,TRUE,TRUE>);
ASSERT(negate<any<FALSE,FALSE,FALSE,FALSE>>);


#endif /* defined(__FunctionalTemplates__logic__) */
