//
//  insertable.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 30.10.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#pragma once
#include <sstream>
#include <type_traits>

namespace
type_traits {

    template<typename TO_INSERT_INTO, typename T_TO_INSERT> struct
    is_insertible {
        private: struct
        not_insertible {};
        
        public: template<typename T_TO_TEST> static auto
        test_insertible (typename std::remove_reference<decltype(std::declval<TO_INSERT_INTO>() << std::declval<T_TO_TEST>())>::type*)
                      -> decltype(std::declval<typename std::add_lvalue_reference<TO_INSERT_INTO>::type>() << std::declval<T_TO_TEST>());
        
        public: template<typename T_TO_TEST> static
        not_insertible
        test_insertible (...);
        
        public: static constexpr bool
        value = std::is_convertible<
                    decltype(test_insertible<T_TO_INSERT>(nullptr)),
                    typename std::add_lvalue_reference<TO_INSERT_INTO>::type
                >::value;
    };

    namespace __testing {
        struct not_insertible_struct {};
        constexpr bool
        test_is_insertible1 = is_insertible<std::ostream,std::string>::value,
        test_is_insertible2 = !is_insertible<std::ostream,not_insertible_struct>::value;
        
        constexpr bool testresult_is_insertible = test_is_insertible1 && test_is_insertible2;
        static_assert(testresult_is_insertible,"error");
        
        
    }
}
