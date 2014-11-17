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
#include <Maybe.h>
#include <curry.h>
#include <stdio.h>
#include <custom_infix.h>
#include <playground.h>

using namespace ftmpl;

/*
Maybe<int> maybetest(int i) {
    return Maybe<int>(8);
}*/


void fun(int a,int b,int c, char w)
{
    std::stringstream ret;
    ret << a << b << c << w;
}

void f(std::string a,std::string b,std::string c)
{
    std::cout << a << b << c;
}

int main(int argc, const char * argv[])
{
    std::list<union_of<int,double,float,std::string>> mylist;
    mylist.emplace_front(33.1f);
    mylist.emplace_front(34.576);
    mylist.emplace_front(77);
    mylist.emplace_front(std::string("Hello World"));
    curry(fun)(4)(7)(88)('X');
//    std::cout << "fff(4,7,88,'X')=" << curry(fun)(4)(7)(88)('X') << std::endl;
    

    
    curry(f)("Hello ")("functional ")("world!");
   
//    curry(printf)("test %f done")(1.23456f);
//    std::cout << "fff(4,7,88)=" << ((fff(4))(7))(88) << std::endl;
    
    std::list<union_of<int,double,float,std::string>>::iterator it2 = mylist.begin();
    
    for(const auto& it: mylist) {
        std::cout << it << std::endl;
    }
    
    union_of<int,wchar_t,float> a(0);
    a=4.4f;
    
    std::cout << "a=" << a << std::endl;
    run_playground();

    return 0;
}

