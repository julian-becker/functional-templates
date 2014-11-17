//
//  result_of.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__result_of__
#define __FunctionalTemplates__result_of__

/// extracts the resulting TRUE or FALSE from T::result
template <typename T> using
result_of = typename T::result;

template <typename T, typename T1> using
result_of_t1 = typename T::template result<T1>;

#endif /* defined(__FunctionalTemplates__result_of__) */
