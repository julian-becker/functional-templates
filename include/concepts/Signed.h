//
//  Signed.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__Signed__
#define __FunctionalTemplates__Signed__

#include <type_traits>

namespace concepts {

    struct Signed {
        template <typename T> struct
        apply : std::is_signed<T> {};
    };
}

#endif /* defined(__FunctionalTemplates__Signed__) */
