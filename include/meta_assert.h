//
//  meta_assert.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__meta_assert__
#define __FunctionalTemplates__meta_assert__

#if defined (ENABLE_TESTS)
#define ASSERT(...) static_assert(__VA_ARGS__::value,#__VA_ARGS__)
#else
#define ASSERT(...) 
#endif

#define ASSERT_NOT(...) ASSERT(!__VA_ARGS__)
#define ASSERT_EQUAL(...) static_assert(std::is_same<__VA_ARGS__>::value, "expected types " #__VA_ARGS__ " to be the same, but they are not")
#define ASSERT_NOT_EQUAL(...) static_assert(!std::is_same<__VA_ARGS__>::value, "expected types " #__VA_ARGS__ " to be different, but they are not")


#endif /* defined(__FunctionalTemplates__meta_assert__) */
