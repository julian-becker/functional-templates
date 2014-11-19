//
//  length.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__length__
#define __FunctionalTemplates__length__

#include <list/detail/dtl_length.h>

#include <fold.h>
#include <meta_types/meta_types.h>

namespace list {
    
    template <typename LIST> using
    length = foldl<__dtl::__count_types,meta_types::uint_<0>,LIST>;

}

#endif /* defined(__FunctionalTemplates__length__) */
