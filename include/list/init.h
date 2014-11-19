//
//  init.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__init__
#define __FunctionalTemplates__init__

#include <list/tail.h>
#include <list/reverse.h>

namespace list {

    template <typename LIST> using
    init = reverse<tail<reverse<LIST>>>;
    
}
#endif /* defined(__FunctionalTemplates__init__) */
