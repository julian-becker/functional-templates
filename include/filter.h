//
//  filter.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__filter__
#define __FunctionalTemplates__filter__

#include <result_of.h>
#include <type_traits>
#include <logic.h>
#include <fold.h>
#include <conditional.h>
#include <meta_assert.h>

namespace prelude {
  namespace list {
  
    //! @cond Doxygen_Suppress
    namespace __dtl {
    
        template <template <typename> class PREDICATE_FN> struct
        __helper {
            template <typename T, typename LIST> struct
            __prepend_if;
            
            template <typename T, template <typename...> class LIST_TEMPLATE, typename...ELEMENTS> struct
            __prepend_if<T,LIST_TEMPLATE<ELEMENTS...>> {
                using result =
                if_true< PREDICATE_FN<T>,
                    LIST_TEMPLATE<T,ELEMENTS...>,
                    LIST_TEMPLATE<ELEMENTS...>
                >;
            };
        };
        
        template <typename LIST_TYPE> struct
        __list_template_of;
        
        template <template <typename...> class LIST_TEMPLATE,typename...ELEMENTS> struct
        __list_template_of<LIST_TEMPLATE<ELEMENTS...>> {
            template <typename...TS> using result = LIST_TEMPLATE<TS...>;
        };
        
        
        
    }
    //! @endcond Doxygen_Suppress
    
    
    /// @brief filters a given LIST using the predicate metafunction PREDICATE_FN.
    /// @tparam PREDICATE_FN the metafunction used for the mapping of the types in the typelist LIST.
    /// @tparam LIST the typelist which is to be mapped using PREDICATE_FN
    template <template <typename> class PREDICATE_FN, typename LIST> using
    filter = foldl<__dtl::__helper<PREDICATE_FN>::template __prepend_if,typename __dtl::__list_template_of<LIST>::template result<>, LIST>;
    
    
    
    template <typename T> using
    is_integral = typename std::conditional<std::is_integral<T>::value,TRUE,FALSE>::type;
    
    ASSERT_EQUAL(is_integral<int>,TRUE);
    ASSERT_EQUAL(is_integral<int>,TRUE);

  }
}

#endif /* defined(__FunctionalTemplates__filter__) */
