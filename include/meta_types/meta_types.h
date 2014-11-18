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
    template <int VALUE> struct
    int_{
        static constexpr int value = VALUE;
    };
}

#endif /* defined(__FunctionalTemplates__meta_types__) */
