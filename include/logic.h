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

#if defined (ENABLE_TESTS)
#define ASSERT(...) static_assert(__VA_ARGS__::value,#__VA_ARGS__)
#else
#define ASSERT(...) 
#endif

#define ASSERT_NOT(...) ASSERT(!__VA_ARGS__)
#define ASSERT_EQUAL(...) static_assert(std::is_same<__VA_ARGS__>::value, "expected types " #__VA_ARGS__ " to be the same, but they are not")
#define ASSERT_NOT_EQUAL(...) static_assert(!std::is_same<__VA_ARGS__>::value, "expected types " #__VA_ARGS__ " to be different, but they are not")



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



struct
static_string {
    private: const char* content;
    private: const size_t size;
    
    public: static_string(const static_string& other) = default;
    public: template <size_t LEN>
    constexpr static_string(const char (&str)[LEN]) : content(str), size(LEN) {}
    constexpr static_string(const char* str,unsigned long len) : content(str), size(len) {}
    public: constexpr operator const char* () const { return content; }
    public: constexpr char operator [] (size_t index) const { return content[index]; }
};


constexpr const static_string test("test");

constexpr static_string
operator "" _str(const char *s, unsigned long len) {
    return static_string(s,len);
}

constexpr auto test2 = "12334"_str;


struct constexpr_functor {
    constexpr constexpr_functor() {}
    constexpr constexpr_functor operator () () const { return constexpr_functor(); }
};


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
    
    
    template <template <typename> class T1, template <typename> class T2> struct
    __equal_t1 {
        using
        result = FALSE;
    };

    template <template <typename> class T> struct
    __equal_t1<T,T> {
        using
        result = TRUE;
    };

}
///! @endcond Doxygen_Suppress

template <typename BOOL1,typename BOOL2> using
equal = result_of<__dtl::__equal<BOOL1,BOOL2>>;

template <template <typename> class T1, template <typename> class T2> using
equal_t1 = result_of<__dtl::__equal_t1<T1,T2>>;

ASSERT(equal<TRUE,TRUE>);
ASSERT_NOT(equal<TRUE,FALSE>);
ASSERT_NOT(equal<FALSE,TRUE>);
ASSERT(equal<FALSE,FALSE>);


ASSERT(equal<negate<FALSE>,TRUE>);


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
        result = result_of<__foldl<META_FUN, META_FUN<INIT,T>, TS...>>;
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
any = foldl<either,FALSE,BOOLS...>;
//any = foldr<either,FALSE,BOOLS...>;  /// alternative implementation

// ###################################################################################

template <typename...BOOLS> using
all = foldl<both,TRUE,BOOLS...>;
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

ASSERT(equal_t1<negate,negate>);


// ###################################################################################

template <typename...TS> struct
type_list {};

// ###################################################################################

//! @cond Doxygen_Suppress
namespace __dtl {

    template <typename T, typename LIST> struct
    __cons;

    template <typename T, template <typename...> class LIST, typename...TS> struct
    __cons<T,LIST<TS...> > {
        using
        result = LIST<T,TS...>;
    };
}
//! @endcond Doxygen_Suppress

template <typename T, typename LIST> using
cons = result_of<__dtl::__cons<T,LIST>>;

// ###################################################################################



// ###################################################################################


//template <template <typename> class FUN, template<typename...> class LIST,typename...TS> using
//map = foldr< compose<cons_t,FUN>, LIST< >, LIST<TS...>>;


#endif /* defined(__FunctionalTemplates__logic__) */
