//
//  logic.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 06.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__logic__
#define __FunctionalTemplates__logic__

#include <type_traits>
#include <result_of.h>
#include <meta_assert.h>
#include <fold.h>
#include <list.h>

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
    
    /// specialization of negate for TRUE, resulting in FALSE
    template <typename BOOL> struct
    __negate<__negate<BOOL>> {
        /// yield FALSE only if argument is TRUE
        using
        result = BOOL;
    };
}
///! @endcond Doxygen_Suppress

template <typename BOOL> using
negate = result_of<__dtl::__negate<BOOL>>;

ASSERT(negate<FALSE>);
ASSERT_NOT(negate<TRUE>);
ASSERT(negate<negate<TRUE>>);
ASSERT_NOT(negate<negate<FALSE>>);

#include <type_traits>
ASSERT(std::is_same<FALSE,FALSE>);


// ###################################################################################

template <typename BOOL> using
id = BOOL;

ASSERT(id<TRUE>);
ASSERT(id<id<TRUE>>);
ASSERT_NOT(id<FALSE>);
ASSERT_EQUAL(FALSE,FALSE);

// ###################################################################################


// ###################################################################################




// ###################################################################################

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
any = foldl<either,FALSE,list::list<BOOLS...>>;
//any = foldr<either,FALSE,BOOLS...>;  /// alternative implementation

// ###################################################################################

template <typename...BOOLS> using
all = foldl<both,TRUE,list::list<BOOLS...>>;
//all = foldr<both,TRUE,BOOLS...>;      /// alternative implementation

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


// ###################################################################################

template <typename...TS> struct
type_list {};

// ###################################################################################


//template <template <typename> class FUN, template<typename...> class LIST,typename...TS> using
//map = foldr< compose<cons_t,FUN>, LIST< >, LIST<TS...>>;


#endif /* defined(__FunctionalTemplates__logic__) */
