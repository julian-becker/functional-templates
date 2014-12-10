//
//  CopyConstructible.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#define ENABLE_TESTS

#include <concepts/concepts.h>
#include "CopyConstructible.h"

using namespace concepts;

ASSERT(CopyConstructible::apply<int>);

// ! @cond Doxygen_Suppress
struct __not_copyable {
    __not_copyable(const __not_copyable&) = delete;
};

struct __copyable {
    __copyable(const __not_copyable&) {};
};

// ! @endcond Doxygen_Suppress

ASSERT(CopyConstructible::apply<__copyable>);
ASSERT_NOT(CopyConstructible::apply<__not_copyable>);
