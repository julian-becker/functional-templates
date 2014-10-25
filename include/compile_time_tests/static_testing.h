#pragma once

namespace testing {

    /// @brief metafunction to evaluate a list of individual compile-time tests
    /// @tparam RESULTS a list of constexpr booleans
    /// @return true if all RESULTS are true
    template <bool...RESULTS> struct
    test_suite;

    //! @cond Doxygen_Suppress

    template <bool RESULT> struct
    test_suite<RESULT> {
        public: static constexpr bool
        value = RESULT;
    };


    template <bool RESULT,bool...REMAINING_TESTS> struct
    test_suite<RESULT,REMAINING_TESTS...> {
        public: static constexpr bool
        value = RESULT && test_suite<REMAINING_TESTS...>::value;
    };

    //! @endcond
    
    namespace __testing {
        static_assert(test_suite<true>::value,"error");
        static_assert(!test_suite<false>::value,"error");
        static_assert(test_suite<true,true>::value,"error");
        static_assert(test_suite<true,true,true>::value,"error");
        static_assert(!test_suite<true,true,false,true>::value,"error");
        static_assert(!test_suite<false,true,true,true>::value,"error");
        static_assert(!test_suite<true,true,true,false>::value,"error");
    };
}