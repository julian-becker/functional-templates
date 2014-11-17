//
//  fold.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__fold__
#define __FunctionalTemplates__fold__

#include <result_of.h>

///! @cond Doxygen_Suppress
namespace __dtl {

    template <template <typename,typename> class META_FUN, typename INIT, typename LIST> struct
    __foldr;

    template <template <typename,typename> class META_FUN, typename INIT, template <typename...> class LIST_TYPE, typename T, typename...TS> struct
    __foldr<META_FUN,INIT,LIST_TYPE<T,TS...>> {
        using
        result = META_FUN<T,result_of<__foldr<META_FUN,INIT,LIST_TYPE<TS...>>>>;
    };


    template <template <typename,typename> class META_FUN, typename INIT, template <typename...> class LIST_TYPE> struct
    __foldr<META_FUN,INIT,LIST_TYPE<>> {
        using
        result = INIT;
    };
}
///! @endcond Doxygen_Suppress

template <template <typename,typename> class META_FUN, typename INIT, typename LIST> using
foldr = result_of<__dtl::__foldr<META_FUN, INIT, LIST>>;

// ###################################################################################

///! @cond Doxygen_Suppress
namespace __dtl {

    template <template <typename,typename> class META_FUN, typename INIT, typename LIST> struct
    __foldl;

    template <template <typename,typename> class META_FUN, typename INIT, template <typename...> class LIST_TYPE, typename T, typename...TS> struct
    __foldl<META_FUN,INIT,LIST_TYPE<T,TS...> > {
        using
        result = result_of<__foldl<META_FUN, META_FUN<INIT,T>, LIST_TYPE<TS...> > >;
    };


    template <template <typename,typename> class META_FUN, typename INIT, template <typename...> class LIST_TYPE> struct
    __foldl<META_FUN,INIT,LIST_TYPE<>> {
        using
        result = INIT;
    };
}
///! @endcond Doxygen_Suppress

template <template <typename,typename> class META_FUN, typename INIT, typename LIST> using
foldl = result_of<__dtl::__foldl<META_FUN, INIT, LIST > >;


#endif /* defined(__FunctionalTemplates__fold__) */
