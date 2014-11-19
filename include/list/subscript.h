//
//  subscript.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__subscript__
#define __FunctionalTemplates__subscript__

#include <list/detail/dtl_subscript.h>

namespace list {
    
    
    /// @brief retrieve the type at index INDEX from the given typelist LIST
    /// @tparam INDEX the index into the typelist LIST
    /// @tparam LIST the typelist from which to retrieve the type at index INDEX
    template <typename INDEX,typename LIST> using
    subscript = result_of<__dtl::__subscript<INDEX, LIST>>;
    
}

#endif /* defined(__FunctionalTemplates__subscript__) */
