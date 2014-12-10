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

namespace
callable {
    template <typename CALLABLE> struct
    callable_traits {
       
        template <template <typename...> class LIST_TYPE> using
        arguments = typename __dtl::__member_fn_arguments_extractor<decltype(&CALLABLE::operator())>::template type<LIST_TYPE>;
        
        using
        wrapper_type = typename __dtl::__call_wrapper_type<decltype(&CALLABLE::operator())>::type;

        using
        result_type = typename __dtl::__call_result_type<decltype(&CALLABLE::operator())>::type;
    };
}
#endif /* defined(__FunctionalTemplates__callable__) */
