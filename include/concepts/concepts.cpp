//
//  concepts.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#define ENABLE_TESTS
#include "concepts.h"

#include <concepts/CopyConstructible.h>
#include <concepts/Signed.h>
#include <list/list.h>
#include <meta_assert.h>

using namespace concepts;

template <
    typename T1,typename T2,
    typename = void
> struct
c_test;

ASSERT_EQUAL(get_type<constrain<int,Signed>>::type,int);
ASSERT_EQUAL(get_type<constrain<constrain<int,Signed>>>::type,int);
ASSERT_EQUAL(get_constraints<constrain<constrain<int,Signed>,CopyConstructible>>::type,list::list<CopyConstructible,Signed>);

//ASSERT(constrain<constrain<signed int, Signed> ,Signed>);

template <
    typename T1,typename T2
> struct
c_test<T1,T2,
  check<T1,constrain<T2,Signed>>
//void_t<typename std::enable_if<all_true<true,constrain<T2,Signed>::value>::value>::type>
  //void_t<typename std::enable_if<constrain<T2,Signed>::value>::type>
>
{
//    ASSERT(concept<T1,CopyConstructible>);
//    ASSERT(concept<T2,CopyConstructible>);
//    static constexpr bool value = second::value;
};

#include <thread>
void duitarenuidaetr(){
    using sgn = constrain<signed int, Signed>;
    using cpyconst = constrain<unsigned, CopyConstructible>;
    static_assert(cpyconst::value,"err");
    sgn s;
    c_test<cpyconst,sgn> t;
}