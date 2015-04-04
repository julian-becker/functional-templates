//
//  CopyConstructible.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__CopyConstructible__
#define __FunctionalTemplates__CopyConstructible__

#include <type_traits>

namespace concepts {

    struct Integral {
        template <typename T> using
        apply = std::integral_constant<bool,std::is_integral<T>::value>;
    };

    struct Signed {
        template <typename T> using
        apply = std::integral_constant<bool,std::is_signed<T>::value>;
    };
    
    struct Unsigned {
        template <typename T> using
        apply = std::integral_constant<bool,std::is_unsigned<T>::value>;
    };
    
    struct CopyConstructible {
        template <typename T> using
        apply = std::integral_constant<bool,std::is_copy_constructible<T>::value>;
    };
}

#endif /* defined(__FunctionalTemplates__CopyConstructible__) */
