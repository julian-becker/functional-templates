//
//  index_of.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 29.10.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef FunctionalTemplates_index_of_h
#define FunctionalTemplates_index_of_h

#include <compile_time_tests/static_testing.h>

namespace ftmpl {

    /// @brief Template metafunction to find the index of a given type T in the given typelist
    /// @tparam T The type to find the index for
    /// @tparam Ts The list in which to search for T
    /// @return value The index of the type T in the list Ts
    template <typename T,typename...Ts> struct
    index_of;

    ///! @cond Doxygen_Suppress

    template <typename T1,typename T2,typename...Ts> struct
    index_of {
        public: static constexpr unsigned
        value = 1+index_of<T,Ts...>::value;
    };


    template <typename T,typename...Ts> struct
    index_of<T,T,Ts...> {
        public: static constexpr unsigned
        value = 0;
    };


    using namespace testing;
    constexpr bool test1 = 0 = index_of<int, int, bool, char, double, float>::value;
    static_assert(assert_all<test1>::value,"error");


    ///! @endcond
}



#endif
