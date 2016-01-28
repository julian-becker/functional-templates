//
//  main.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.10.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include <iostream>
#include <string>
#include <list>
#include <curry.h>
#include <stdio.h>
#include <custom_infix.h>
#include "playground.h"
#include <callable/callable.h>
#include <words/forth.h>
#include <factory_evolution.h>

int main(int argc, const char * argv[])
{
    //test_callable();
    //run_playground();
    //test_curry();
    test_polcies();
/*    forth_test();
    for(auto& x : 10 <DOWN-TO> 1)
        std::cout << "x=" << x << std::endl;
    for(auto& x : 10 <UP-TO> 17)
        std::cout << "x=" << x << std::endl;
        */
    return 0;
}

