//
//  pair.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 22.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__pair__
#define __FunctionalTemplates__pair__

namespace
list {
    template <typename FIRST, typename SECOND> struct
    pair {
        public: using
        first = FIRST;
        
        public: using
        second = SECOND;
    };
}

#endif /* defined(__FunctionalTemplates__pair__) */
