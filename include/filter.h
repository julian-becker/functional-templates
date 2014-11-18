//
//  filter.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__filter__
#define __FunctionalTemplates__filter__

#include <list/detail/dtl_filter.h>
#include <fold.h>


namespace list {
  
    /// @brief filters a given LIST using the predicate metafunction PREDICATE_FN.
    /// @tparam PREDICATE_FN the metafunction used for the mapping of the types in the typelist LIST.
    /// @tparam LIST the typelist which is to be mapped using PREDICATE_FN
    template <template <typename> class PREDICATE_FN, typename LIST> using
    filter = foldl<__dtl::__helper<PREDICATE_FN>::template cons_if, clear<LIST>, LIST>;


}

#endif /* defined(__FunctionalTemplates__filter__) */
