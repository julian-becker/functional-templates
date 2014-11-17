//
//  equal.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__equal__
#define __FunctionalTemplates__equal__

#include <logic.h>
#include <meta_assert.h>
#include <result_of.h>

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


#endif /* defined(__FunctionalTemplates__equal__) */
