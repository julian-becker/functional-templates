//
//  reverse.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__reverse__
#define __FunctionalTemplates__reverse__

#include <list/detail/dtl_reverse.h>

#include <list/clear.h>

namespace list {
    
    /// @brief reverses the types in the specified type list LIST
    template <typename LIST> using
    reverse = result_of<__dtl::__reverse<LIST,clear<LIST>>>;
    
}

#endif /* defined(__FunctionalTemplates__reverse__) */
