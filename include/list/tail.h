//
//  tail.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__tail__
#define __FunctionalTemplates__tail__

#include <list/detail/dtl_tail.h>
#include <result_of.h>

namespace list {
    
    template <typename LIST> using
    tail = result_of<__dtl::__tail<LIST>>;
}

#endif /* defined(__FunctionalTemplates__tail__) */
