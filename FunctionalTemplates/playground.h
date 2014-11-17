//
//  playground.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 08.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#pragma once
#include <iostream>

void run_playground();


template <typename X>
struct Generic {};

/*

template <template <typename> class CLASS> struct
inst_test {
    template <typename T, CLASS> struct
    inst_test2
    static constexpr bool value = false;
    
};

template <template <typename> class CLASS, typename T, typename U> struct
inst_test<HKT<T>:

template<class T>
struct HKT {
  template<class U> // this looks like e.g. rebind in std::allocators
  auto F(U) -> HKT<U>;
};


template <template <class> class HKT, class T>
constexpr bool
HKTWithTemplateMemberFunctionF () {
  return
    false; //requires(HKT<T> h);
}

#include <functional>
#include <utility>
#include <type_traits>

template<class U, class T=void>
auto F(U) -> HKT<U>;

template<class U>
auto F(U)->std::enable_if<true, HKT<U>>;

template<class U>
auto F(U)->std::enable_if<false, HKT<U>>;
*/

