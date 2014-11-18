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
#include <list.h>
#include <append.h>


namespace list {
  
    //! @cond Doxygen_Suppress
    namespace __dtl {
    
        using namespace list;
        
        template <template <typename> class PREDICATE_FN> struct
        __helper {
            template <typename LIST, typename T> using
            cons_if =
                if_true< PREDICATE_FN<T>,
                    append<T,LIST>,
                    LIST>;
        };
        
        
    }
    //! @endcond Doxygen_Suppress
    
    
    /// @brief filters a given LIST using the predicate metafunction PREDICATE_FN.
    /// @tparam PREDICATE_FN the metafunction used for the mapping of the types in the typelist LIST.
    /// @tparam LIST the typelist which is to be mapped using PREDICATE_FN
    template <template <typename> class PREDICATE_FN, typename LIST> using
    filter = foldl<__dtl::__helper<PREDICATE_FN>::template cons_if, clear<LIST>, LIST>;
    
    
    
    template <typename T> using
    is_integral = typename std::conditional<std::is_integral<T>::value,TRUE,FALSE>::type;
    
    ASSERT_EQUAL(is_integral<int>,TRUE);
    ASSERT_EQUAL(is_integral<double>,FALSE);
    ASSERT_EQUAL(if_true< is_integral<int>,
                    cons<int,list<>>,
                    list<>>,list<int>);
    
    ASSERT_EQUAL(filter<is_integral,list<double>>,
                 list<>);
    ASSERT_EQUAL(filter<is_integral,list<double,int,float,long>>,
                 list<int,long>);

}

#endif /* defined(__FunctionalTemplates__filter__) */
