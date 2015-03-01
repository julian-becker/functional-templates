//
//  dtl_callable.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__callable__
#   error "this file must never be included directly"
#endif

#include <functional>

namespace
callable {
    namespace
    __dtl {
    
        template <typename> struct
        __member_fn_arguments_extractor;

        template <typename CALLABLE, typename R,typename...ARG_TYPES> struct
        __member_fn_arguments_extractor<R (CALLABLE::*)(ARG_TYPES...) const> {
            public: template <template <typename...> class LIST_TYPE> using
            result = LIST_TYPE<ARG_TYPES...>;
        };
        
        template <typename CALLABLE, typename R,typename...ARG_TYPES> struct
        __member_fn_arguments_extractor<R (CALLABLE::*)(ARG_TYPES...)> {
            public: template <template <typename...> class LIST_TYPE> using
            result = LIST_TYPE<ARG_TYPES...>;
        };
        
       
        template <typename T> struct
        __call_wrapper_type;

        template <typename CALLABLE, typename R, typename...ARG_TYPES> struct
        __call_wrapper_type<R (CALLABLE::*)(ARG_TYPES...) const> {
            public: using
            result = std::function<R(ARG_TYPES...)>;
        };
        
        template <typename CALLABLE, typename R, typename...ARG_TYPES> struct
        __call_wrapper_type<R (CALLABLE::*)(ARG_TYPES...)> {
            public: using
            result = std::function<R(ARG_TYPES...)>;
        };
        
        
        template <typename T> struct
        __call_result_type;

        template <typename CALLABLE, typename R, typename...ARG_TYPES> struct
        __call_result_type<R (CALLABLE::*)(ARG_TYPES...) const> {
            public: using
            result = R;
        };

        template <typename CALLABLE, typename R, typename...ARG_TYPES> struct
        __call_result_type<R (CALLABLE::*)(ARG_TYPES...)> {
            public: using
            result = R;
        };
        
    }
}
