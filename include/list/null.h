//
//  null.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 18.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__null__
#define __FunctionalTemplates__null__

#include <list/clear.h>
#include <equal.h>

namespace list {

    template <typename LIST> using
    null = equal<LIST,clear<LIST>>;

}

#endif /* defined(__FunctionalTemplates__null__) */
