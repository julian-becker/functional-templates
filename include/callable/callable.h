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

namespace
callable {
    template <typename CALLABLE> struct
    callable_traits {
       
        template <template <typename...> class LIST_TYPE> using
        arguments = typename __dtl::__member_fn_arguments_extractor<decltype(&CALLABLE::operator())>::template result<LIST_TYPE>;
        
        using
        wrapper_type = ::result_of<__dtl::__call_wrapper_type<decltype(&CALLABLE::operator())>>;

        using
        result_type = ::result_of<__dtl::__call_result_type<decltype(&CALLABLE::operator())>>;
    };
    
    
    template <typename CALLABLE_TYPE> struct
    callable {
        //----
        public: typename callable_traits<CALLABLE_TYPE>::wrapper_type
        function;
        
        //----
        public:
        callable(CALLABLE_TYPE function) : function(function) {}
        
        
        public: using
        t_return = typename callable_traits<CALLABLE_TYPE>::result_type;
        
        //----
        private: template <typename...Ts, int...ARGUMENT_INDICES> t_return
        executeCall(
                    const std::tuple<Ts...>&& arguments,
                    list::int_list<ARGUMENT_INDICES...>)
        {
            return function(std::get<ARGUMENT_INDICES>(arguments)...);
        }
        
        //----
        public: template <typename...Ts> t_return
        operator() (const std::tuple<Ts...>& arguments)
        {
            return executeCall(
                        std::move(arguments),
                        list::int_range_up_to<sizeof...(Ts)>());
        }
    };

}
#endif /* defined(__FunctionalTemplates__callable__) */
