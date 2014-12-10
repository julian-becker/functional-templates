//
//  join_n.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 27.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__join_n__
#define __FunctionalTemplates__join_n__

#include <list/join.h>
#include <list/clear.h>
#include <list/head.h>
#include <fold.h>

namespace list {
    
    namespace __dtl {
        template <typename T1, typename T2> struct
        __join_2 {
            using
            result = join<T1,T2>;
        };
    }
    
    /// @brief metafunction JOIN.
    /// @tparam LISTS the lists to join
    /// @returns a new list that is the concatenation of the LISTS
    template <typename LIST, typename...LISTS> using
    join_n = foldl<join,LIST,list<LISTS...> >;

}

#endif /* defined(__FunctionalTemplates__join_n__) */
