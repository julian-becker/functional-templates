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
#include <list>

using namespace ftmpl;

int main(int argc, const char * argv[])
{
    std::list<union_of<int,double,float,std::string>> mylist;
    mylist.emplace_front(33.1f);
    mylist.emplace_front(34.576);
    mylist.emplace_front(77);
    mylist.emplace_front(std::string("Hello World"));
    
    std::list<union_of<int,double,float,std::string>>::iterator it2 = mylist.begin();
    
    for(const auto& it: mylist) {
        std::cout << it << std::endl;
    }
    
    return 0;
}

