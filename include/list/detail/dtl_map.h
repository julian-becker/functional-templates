//
//  dtl_map.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__map__
#   error "this file must never be included directly"
#endif

namespace list {
  
    //! @cond Doxygen_Suppress
    namespace __dtl {
    // ! 
        template <template <typename> class FN, typename LIST> struct
        __map;
        
        template <template <typename> class FN, template <typename...> class LIST_TEMPLATE, typename...ELEMENTS> struct
        __map<FN,LIST_TEMPLATE<ELEMENTS...>> {
            using result = LIST_TEMPLATE<FN<ELEMENTS>...>;
        };
    }
    //! @endcond Doxygen_Suppress
    
}
