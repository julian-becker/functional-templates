//
//  value_list.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__value_list__
#define __FunctionalTemplates__value_list__

#include <result_of.h>

namespace
list {
    
    template<int...VALUES> struct
    int_list {
    };

    template<int N1, int N2, int...S> struct
    make_int_range_list : make_int_range_list<N1, N2-1, N2-1, S...> {
    };
    
    template<int N, int...S> struct
    make_int_range_list<N,N,S...> {
        using
        result = int_list<S...>;
    };
    
    template <int N> using
    int_range_up_to = result_of<make_int_range_list<0,N>>;
    
}

#endif /* defined(__FunctionalTemplates__value_list__) */
