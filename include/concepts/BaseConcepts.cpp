//
//  CopyConstructible.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#define ENABLE_TESTS

#include <concepts/concepts.h>
#include "BaseConcepts.h"

using namespace concepts;

CONCEPT_ASSERT(Integral::apply<int>());
CONCEPT_ASSERT_NOT(Integral::apply<double>());

// ! @cond Doxygen_Suppress
struct __not_copyable {
    __not_copyable(const __not_copyable&) = delete;
};

struct __copyable {
    __copyable(const __not_copyable&) {};
};

// ! @endcond Doxygen_Suppress

CONCEPT_ASSERT(CopyConstructible::apply<__copyable>());
CONCEPT_ASSERT_NOT(CopyConstructible::apply<__not_copyable>());
