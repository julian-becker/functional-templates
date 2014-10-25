//
//  has_operator.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.10.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#pragma once

#define ___DEFINE_HAS_RELATIONAL_OPERATOR(name,op) \
    template<typename T> struct                                                             \
    has_ ## name {                                                                          \
        private: struct                                                                     \
        no_such_operator {};                                                                \
                                                                                            \
        private: template<typename T_TO_TEST> static auto                                   \
        test_ ## name (decltype(std::declval<T_TO_TEST>() op std::declval<T_TO_TEST>())*)   \
                    -> decltype(std::declval<T_TO_TEST>() op std::declval<T_TO_TEST>());    \
                                                                                            \
        private: template<typename T_TO_TEST> static no_such_operator                       \
        test_ ## name (...);                                                                \
                                                                                            \
        public: static constexpr bool                                                       \
        value = std::is_convertible<                                                        \
                    decltype(test_ ## name<T>(nullptr)),                                    \
                    bool                                                                    \
                >::value;                                                                   \
    }

namespace
type_traits {
    ___DEFINE_HAS_RELATIONAL_OPERATOR(eq,==);        ///< define has_eq<T>
    ___DEFINE_HAS_RELATIONAL_OPERATOR(neq,!=);       ///< define has_neq<T>
    ___DEFINE_HAS_RELATIONAL_OPERATOR(lt,<);         ///< define has_lt<T>
    ___DEFINE_HAS_RELATIONAL_OPERATOR(lteq,<=);      ///< define has_lteq<T>
    ___DEFINE_HAS_RELATIONAL_OPERATOR(gt,>);         ///< define has_gt<T>
    ___DEFINE_HAS_RELATIONAL_OPERATOR(gteq,>=);      ///< define has_gteq<T>
    
    namespace __testing {
        struct struct_with_no_comparison_operators {};
        constexpr bool
        test1 = has_eq<int>::value,
        test2 = has_neq<int>::value,
        test3 = has_lt<int>::value,
        test4 = has_lteq<int>::value,
        test5 = has_gteq<int>::value,
        test6 = has_gteq<int>::value,
        test7 = !has_eq<struct_with_no_comparison_operators>::value;
        
        constexpr bool testresult = test1;
        static_assert(testresult,"error");
    }
}




#undef ___DEFINE_HAS_RELATIONAL_OPERATOR