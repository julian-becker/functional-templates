//
//  head.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__head__
#define __FunctionalTemplates__head__

#include <list/detail/dtl_head.h>
#include <result_of.h>


namespace list {
    
    /// @brief evaluates to the first type in the given typelist LIST
    /// @tparam LIST a type list
    template <typename LIST> using
    head = result_of<__dtl::__head<LIST>>;

}

#endif /* defined(__FunctionalTemplates__head__) */
