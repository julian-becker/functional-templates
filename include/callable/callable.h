//
//  callable.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__callable__
#define __FunctionalTemplates__callable__

#include <callable/detail/dtl_callable.h>
#include <list/value_list.h>
#include <result_of.h>
#include <list/length.h>
#include <list/list.h>

namespace
callable {
    template <typename CALLABLE> struct
    callable_traits {
       
        template <template <typename...> class LIST_TYPE> using
        arguments = typename __dtl::__member_fn_arguments_extractor<decltype(&CALLABLE::operator())>::template result<LIST_TYPE>;
        
        static constexpr unsigned
        args_count = list::template length<arguments<list::list>>::value;
        
        using
        wrapper_type = ::result_of<__dtl::__call_wrapper_type<decltype(&CALLABLE::operator())>>;

        using
        result_type = ::result_of<__dtl::__call_result_type<decltype(&CALLABLE::operator())>>;
    };
    
    /// @brief Wrapper for callable objects allowing you to call them using a tuple containing all the call arguments
    template <typename CALLABLE_TYPE> struct
    callable {
        /// @brief The wrapped callable instance
        public: typename callable_traits<CALLABLE_TYPE>::wrapper_type
        function;

        /// @brief This is the std::tuple<call_arg_1_type,call_arg_2_type,etc>, i.e. a tuple containing all function call arguments
        public: using
        call_args_tuple = typename callable_traits<CALLABLE_TYPE>::template arguments<std::tuple>;
        
        /// @brief Constructor
        /// @param function     The wrapped callable object
        public:
        callable(CALLABLE_TYPE function) : function(function) {}
        
        /// @brief the return type of a call to the callable instance's operator()
        private: using
        return_type = typename callable_traits<CALLABLE_TYPE>::result_type;
        
        /// @brief helper function to unpack the contents of the given tuple into the function call arguments
        private: template <typename...Ts, int...ARGUMENT_INDICES> return_type
        executeCall(
                    const std::tuple<Ts...>&& arguments,
                    list::int_list<ARGUMENT_INDICES...>)
        {
            return function(std::get<ARGUMENT_INDICES>(arguments)...);
        }
        

        /// @brief calls the wrapped function with the arguments contained in the tuple 'arguments'
        /// @param arguments      The tuple of arguments that will be expanded in the call to the wrapped callable
        public: return_type
        operator() (const call_args_tuple& arguments)
        {
            return executeCall(
                        std::move(arguments),
                        list::int_range_up_to<callable_traits<CALLABLE_TYPE>::args_count>());
        }
    };

}
#endif /* defined(__FunctionalTemplates__callable__) */
