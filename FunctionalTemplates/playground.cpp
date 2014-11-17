//
//  playground.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 08.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "playground.h"
#include <custom_infix.h>
#include <chrono>
#include <string>
#include <sstream>
#include <logic.h>

template<class T>
struct A {
    enum E : T;
};

template<class T>
enum A<T>::E : T { eT };

//template<>
//enum A<char>::E : char { echar }; // ill-formed, A<char>::E was instantiated

auto test13 = A<char>::E::eT;

void run_playground() {
/*
    using T = decltype( has_template_arg::test<HKT>(nullptr,(int*)0));
    std::cout << std::declval<has_template_arg::test<HKT>>(nullptr)::value << std::endl;
    std::cout << std::declval<has_template_arg::test<Generic>>(nullptr)::value << std::endl;
*/
    
/*  std::vector<int> v(100000);
    std::iota (std::begin(v), std::end(v), 0);

    auto t1 = std::chrono::system_clock::now();
    int u;

    for(int i = 0; i<= 20000; i++)
        for(int j = 0; j<= i; j++)
            u+=i+j;
    
    auto t2 = std::chrono::system_clock::now();
    
    for(int i : 0 <UPTO> 20000)
        for(int j : 0 <UPTO> i)
            u+=i+j;
    
    auto t3 = std::chrono::system_clock::now();

    auto d12 = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count(),
    d23 = std::chrono::duration_cast<std::chrono::milliseconds>(t3-t2).count();
    std::cout << "results: delta1 = "<<d12 << ", delta2 = "<<d23 << std::endl;
*/
    
    std::cout << "uaidetrunaedtur"_str << std::endl;
}