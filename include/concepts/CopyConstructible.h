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
/// for testing purposes only
#include <meta_assert.h>

namespace concepts {

    struct CopyConstructible {
        template <typename T> struct
        apply : std::is_copy_constructible<T> {};
    };
    
}

#endif /* defined(__FunctionalTemplates__CopyConstructible__) */
