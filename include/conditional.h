//
//  conditional.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 17.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__conditional__
#define __FunctionalTemplates__conditional__

#include <logic.h>
#include <meta_assert.h>

///! @cond Doxygen_Suppress
namespace __dtl {

    template <typename BOOL,typename IF_TRUE,typename ELSE> struct
    __if_true {
        using
        result = ELSE;
    };

    template <typename IF_TRUE,typename ELSE> struct
    __if_true<TRUE,IF_TRUE,ELSE> {
        using
        result = IF_TRUE;
    };
}
///! @endcond Doxygen_Suppress

template <typename BOOL,typename IF_TRUE,typename ELSE>
using if_true = result_of<__dtl::__if_true<BOOL,IF_TRUE,ELSE>>;

ASSERT(if_true<TRUE,TRUE,FALSE>);
ASSERT_NOT(if_true<FALSE,TRUE,FALSE>);
ASSERT(if_true<FALSE,FALSE,TRUE>);
ASSERT_NOT(if_true<TRUE,FALSE,TRUE>);

// ###################################################################################

template <typename BOOL, typename IF_TRUE, typename ELSE> using
if_false = negate<if_true<BOOL, IF_TRUE, ELSE>>;

ASSERT_NOT(if_false<TRUE,TRUE,FALSE>);
ASSERT(if_false<FALSE,TRUE,FALSE>);
ASSERT_NOT(if_false<FALSE,FALSE,TRUE>);
ASSERT(if_false<TRUE,FALSE,TRUE>);


#endif /* defined(__FunctionalTemplates__conditional__) */
