//
//  main.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.10.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include <iostream>
#include <type_traits/has_operator.h>
#include <compile_time_tests/static_testing.h>
#include <any_of.h>
#include <string>

using namespace ftmpl;

int main(int argc, const char * argv[])
{
    any_of<int,std::string> some1(10);
    int i = any_of<int,std::string>(10).as<int>();
    std::cout << "i="<<i<<std::endl << "some1="<<some1.as<int>() << std::endl;
    some1 = std::string("Hello World");
    std::cout << "some1="<<some1.as<std::string>() << std::endl;
    
    return 0;
}

