//
//  Factory.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 22.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#include "Factory.h"

#include <iostream>
#include <string>
#include <memory>

struct Base {};
struct Derived : Base {
    Derived(std::string arg) {
        std::cout << "Constructing derived with " << arg << "\n";
    }
};
struct Derived2 : Base {
    Derived2(std::string arg,int i) {
        std::cout << "Constructing derived2 with " << arg << " and "<<i<<"\n";
    }
};

using namespace factory;

int run_playground() {

    std::unordered_map<std::string, std::type_index> keyToTypeMap {
        {"Derived2",std::type_index(typeid(Derived2))},
        {"Derived",std::type_index(typeid(Derived))}
    };
    std::unique_ptr<FactorySelector<Base,std::string>> selector(new FactorySelector<Base,std::string>(keyToTypeMap));
    {
        selector->setup<Derived>(std::string("Test"));
        selector->setup<Derived2>(std::string("Test2"),42);
    }

    std::unique_ptr<Base> factory = selector->get("Derived2")->create();

    return 0;
}