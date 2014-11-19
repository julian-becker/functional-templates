//
//  dtl_length.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__length__
#   error "this file should never be included directly"
#endif

#include <meta_types/meta_types.h>

namespace list {

    // ! @cond Doxygen_Suppress
    namespace __dtl {
        
        template <typename COUNTER, typename T> using
        __count_types = meta_types::inc<COUNTER>; /// increment COUNTER for each T

    }
    // ! @endcond
    
}
