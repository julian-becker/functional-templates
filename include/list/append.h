//
//  append.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__append__
#define __FunctionalTemplates__append__

#include <list/join.h>
#include <list/clear.h>
#include <list/cons.h>

namespace list {
    
    /// @brief metafunction APPEND.
    /// @tparam T       the type to add to the end of the typelist LIST.
    /// @tparam LIST    the list, to which to add T at the end.
    template <typename T, typename LIST> using
    append = join<LIST,cons<T,clear<LIST>>>;
}

#endif /* defined(__FunctionalTemplates__append__) */
