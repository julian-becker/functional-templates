//
//  Maybe.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 03.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#pragma once

#include <any_of.h>

struct Nothing {};

template <typename T> using Maybe = ftmpl::union_of<Nothing,T>;