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
#include <list.h>

///! @cond Doxygen_Suppress
namespace __dtl {

    using namespace list;


    template <template <typename,typename> class META_FUN, typename INIT, typename LIST> struct
    __foldr {
        using
        result = META_FUN<
                    head<LIST>,
                    result_of<__foldr<
                                META_FUN,
                                INIT,
                                tail<LIST> >
                    >
                >;
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
    
    using namespace list;

    template <template <typename,typename> class META_FUN, typename INIT, typename LIST> struct
    __foldl {
        using
        result = result_of<__foldl<META_FUN, META_FUN<INIT,head<LIST>>, tail<LIST> > >;
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
