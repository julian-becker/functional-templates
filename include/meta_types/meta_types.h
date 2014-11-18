//
//  meta_types.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__meta_types__
#define __FunctionalTemplates__meta_types__

namespace meta_types {

    template <typename T, T VALUE> struct
    value_type {
        static constexpr T
        value = VALUE;
    };

    /// @brief wraps an int some_int into a type int_<some_int>
    template <int VALUE> using
    int_ = value_type<int, VALUE>;
    
    
    /// @brief wraps an unsigned int some_uint into a type uint_<some_uint>
    template <unsigned int VALUE> using
    uint_ = value_type<unsigned int, VALUE>;
}

#endif /* defined(__FunctionalTemplates__meta_types__) */
