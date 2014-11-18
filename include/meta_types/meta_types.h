//
//  meta_types.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__meta_types__
#define __FunctionalTemplates__meta_types__

#include <equal.h>
#include <logic.h>

#include <meta_assert.h>

namespace meta_types {

    /// @brief Wrapper type that makes a concrete non-type template argument into a type
    template <typename T, T VALUE> struct
    value_type {
        /// the value to wrap
        static constexpr T
        value = VALUE;
        
        /// the actual type of the enclosed value
        using type = T;
    };

    /// @brief wraps an int some_int into a type int_<some_int>
    template <int VALUE> using
    int_ = value_type<int, VALUE>;
    
    /// @brief wraps an unsigned int some_uint into a type uint_<some_uint>
    template <unsigned int VALUE> using
    uint_ = value_type<unsigned int, VALUE>;
    
    /// @brief wraps a boolean value into a type
    template <bool VALUE> using
    bool_ = value_type<bool, VALUE>;
    
    
    /// @brief evaluates to true if VALUE is a value_type for 0
    template <typename VALUE> using
    zero = bool_<VALUE::value == static_cast<typename VALUE::type>(VALUE::value)>;
    
    
    ASSERT(zero<int_<0>>);
    ASSERT_NOT(zero<int_<1>>);
    ASSERT(zero<uint_<0>>);
    ASSERT_NOT(zero<uint_<1>>);
}

#endif /* defined(__FunctionalTemplates__meta_types__) */
