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
    is_zero = bool_<VALUE::value == static_cast<typename VALUE::type>(VALUE::value)>;


    /// @brief decrements the given value by 1
    template <typename VALUE> using
    dec = value_type<typename VALUE::type, static_cast<typename VALUE::type>(VALUE::value-1)>;

    /// @brief increments the given value by 1
    template <typename VALUE> using
    inc = value_type<typename VALUE::type, static_cast<typename VALUE::type>(VALUE::value+1)>;

    /// @brief encapsulates a zero of the type as the value in VALUE
    template <typename VALUE> using
    zero = value_type<typename VALUE::type, static_cast<typename VALUE::type>(0)>;
    
}

#endif /* defined(__FunctionalTemplates__meta_types__) */
