//
//  length.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__length__
#define __FunctionalTemplates__length__

#include <meta_types/meta_types.h>

// for tests only:
#include <meta_assert.h>
#include <list/list.h>


namespace list {

    // ! @cond Doxygen_Suppress
    namespace __dtl {
        template <typename LIST> struct
        __length;
       
        template <template <typename...> class LIST_TYPE,typename...TS> struct
        __length<LIST_TYPE<TS...>> {
            using result = meta_types::uint_<sizeof...(TS)>;
        };
    }
    // ! @endcond
    
    template <typename LIST> using
    length = result_of<__dtl::__length<LIST>>;
    
    ASSERT_EQUAL(length<list<int,double,wchar_t>>,meta_types::uint_<3>);
    ASSERT_EQUAL(length<list<>>,meta_types::uint_<0>);
}

#endif /* defined(__FunctionalTemplates__length__) */
