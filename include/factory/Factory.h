//
//  Factory.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 22.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#pragma once
#include <memory> // for std::unique_ptr
#include <functional> // for std::function
#include <type_traits> // for std::enable_if and std::is_base_of

namespace
factory {
    
    //
    template <typename BASE> struct
    IFactory {
        public: virtual std::unique_ptr<BASE>
        create() const = 0;
        
        public: virtual
        ~IFactory() throw() {}
    };


    template <typename BASE>
    struct
    CFactory : public IFactory<BASE> {
        private: std::function<std::unique_ptr<BASE>()>
        creatorFn;
        
        template <
            typename DERIVED,
            typename...DERIVED_CONSTRUCTOR_ARGS,
            typename std::enable_if<std::is_base_of<BASE, DERIVED>::value>::type* = nullptr
        >
        CFactory(DERIVED_CONSTRUCTOR_ARGS&&...args)
        : creatorFn([&]{
            return std::unique_ptr<BASE>(new DERIVED(std::forward<DERIVED_CONSTRUCTOR_ARGS>(args)...));
          }) {}
        
        public: template <
            typename DERIVED,
            typename...DERIVED_CONSTRUCTOR_ARGS,
            typename std::enable_if<std::is_base_of<BASE, DERIVED>::value>::type* = nullptr
        > void
        setup(DERIVED_CONSTRUCTOR_ARGS&&...args) {
            creatorFn = [&]{
                return std::unique_ptr<BASE>(new DERIVED(std::forward<DERIVED_CONSTRUCTOR_ARGS>(args)...));
            };
        }
    };
    
};