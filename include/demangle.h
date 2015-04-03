//
//  demangle.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 03.04.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#ifndef FunctionalTemplates_demangle_h
#define FunctionalTemplates_demangle_h

#include <cxxabi.h>
#include <string>
#include <cstdlib>

template <typename T>
std::string demangle() {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status),
        std::free
    };
    return (status==0) ? res.get() : typeid(T).name() ;
}

#endif
