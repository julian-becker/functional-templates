//
//  type_at.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 29.10.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef FunctionalTemplates_type_at_h
#define FunctionalTemplates_type_at_h

namespace ftmpl {

    /// @brief Template metafunction to get the type at index N in the given typelist
    /// @tparam N The index into the typelist Ts
    /// @tparam Ts The list from which to retrieve the Nth type
    /// @return type The type at index N in the typelist
    template <unsigned N,typename...Ts> struct
    type_at;


    ///! @cond Doxygen_Suppress

    template <typename T,typename...Ts> struct
    type_at<0,T,Ts...> {
        public: using type = T;
    };

    template <unsigned N,typename T,typename...Ts> struct
    type_at<N,T,Ts...> {
        public: using type = typename type_at<N-1,Ts...>::type;
    };

    namespace {
    
        using namespace testing;
        constexpr bool test_type_at = assert_all<
            std::is_same<int,    type_at<0, int, bool, char, double, float>::type>::value,
            std::is_same<bool,   type_at<1, int, bool, char, double, float>::type>::value,
            std::is_same<char,   type_at<2, int, bool, char, double, float>::type>::value,
            std::is_same<double, type_at<3, int, bool, char, double, float>::type>::value,
            std::is_same<float,  type_at<4, int, bool, char, double, float>::type>::value>::value;
        static_assert(test_type_at,"error");
    }

    ///! @endcond
}


#endif
