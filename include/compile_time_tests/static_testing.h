#pragma once

namespace testing {

    /// @brief metafunction to evaluate a list of individual compile-time tests
    /// @tparam RESULTS a list of constexpr booleans
    /// @return true if all RESULTS are true
    template <bool...RESULTS> struct
    assert_all;

    //! @cond Doxygen_Suppress

    template <bool RESULT> struct
    assert_all<RESULT> {
        public: static constexpr bool
        value = RESULT;
    };


    template <bool RESULT,bool...REMAINING_TESTS> struct
    assert_all<RESULT,REMAINING_TESTS...> {
        public: static constexpr bool
        value = RESULT && assert_all<REMAINING_TESTS...>::value;
    };

    //! @endcond
    
    
    
    /// @brief metafunction to evaluate a list of individual compile-time tests
    ///        and returns true if any one of them succeeds
    /// @tparam RESULTS a list of constexpr booleans
    /// @return true if any RESULT is true
    template <bool...RESULTS> struct
    assert_any;

    //! @cond Doxygen_Suppress

    template <bool RESULT> struct
    assert_any<RESULT> {
        public: static constexpr bool
        value = RESULT;
    };


    template <bool RESULT,bool...REMAINING_TESTS> struct
    assert_any<RESULT,REMAINING_TESTS...> {
        public: static constexpr bool
        value = RESULT || assert_any<REMAINING_TESTS...>::value;
    };

    //! @endcond
    
    
    
    /// @brief metafunction to evaluate a list of individual compile-time tests
    ///        and returns true if any one of them succeeds
    /// @tparam RESULTS a list of constexpr booleans
    /// @return true if any RESULT is true
    template <bool...RESULTS> struct
    assert_none {
        /// the static return value. Is true if none of the RESULTS is true.
        public: static constexpr bool
        value = !assert_any<RESULTS...>::value;
    };
    
    namespace __testing {
        // test assert_all
        static_assert(assert_all<true>::value,"error");
        static_assert(!assert_all<false>::value,"error");
        static_assert(assert_all<true,true>::value,"error");
        static_assert(!assert_all<false,false,false>::value,"error");
        static_assert(!assert_all<true,true,false,true>::value,"error");
        static_assert(!assert_all<false,true,true,true>::value,"error");
        static_assert(!assert_all<true,true,true,false>::value,"error");
        
        // test assert_any
        static_assert(assert_any<true>::value,"error");
        static_assert(!assert_any<false>::value,"error");
        static_assert(assert_any<true,true>::value,"error");
        static_assert(!assert_any<false,false,false>::value,"error");
        static_assert(assert_any<true,true,true>::value,"error");
        static_assert(assert_any<true,true,false,true>::value,"error");
        static_assert(assert_any<false,true,true,true>::value,"error");
        static_assert(assert_any<true,true,true,false>::value,"error");
        
        // test assert_none
        static_assert(!assert_none<true>::value,"error");
        static_assert(assert_none<false>::value,"error");
        static_assert(!assert_none<true,true>::value,"error");
        static_assert(assert_none<false,false,false>::value,"error");
        static_assert(!assert_none<true,true,true>::value,"error");
        static_assert(!assert_none<true,true,false,true>::value,"error");
        static_assert(!assert_none<false,true,true,true>::value,"error");
        static_assert(!assert_none<true,true,true,false>::value,"error");
        
    };
}