//
//  actor.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "actor.h"

#include <iostream>

using namespace multithreading;

struct
consuming_actor : actor {
    private: virtual void
    process(const message& msg) {
        msg.get_dispatcher()
        .handle([](init_message) { std::cout << "init_message\n";})
        .handle([](unsigned u)   { std::cout << "unsigned: "<<u<<"\n";})
        .handle([](unsigned u,std::string s)   { std::cout << "unsigned: "<<u<<", string="<<s<<"\n";})
        .handle([](int i)        { std::cout << "int: "<<i<<"\n";})
        .handle([](std::string s){ std::cout << "std::string: "<<s<<"\n";});
    }
};