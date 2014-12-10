//
//  concepts.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 25.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__concepts__
#define __FunctionalTemplates__concepts__

#include <type_traits>
#include <list/list.h>
#include <list/cons.h>
#include <list/join.h>
#include <logic/logic.h>

namespace concepts {


    template <bool...> struct
    all_true {
        static constexpr bool
        value = true;
    };
    
    template <bool b,bool...rest> struct
    all_true<b,rest...> {
        static constexpr bool
        value = b && all_true<rest...>::value;
    };
    
    
    
    template <typename TYPE, typename CONCEPT_LIST> struct
    conceive;
    
    template <typename TYPE, typename...CONCEPTS> struct
    conceive<TYPE,list::list<CONCEPTS...>> {
        using
        constraints = list::list<CONCEPTS...>;
        
        template<typename T> struct
        apply {
            static constexpr bool
            value = all_true<CONCEPTS::template apply<TYPE>::value...>::value;
        };
        
        using
        type = TYPE;
        
        static constexpr bool
        value =apply<TYPE>::value;
        
        static_assert(value,"invalid concept instantiation");
    };
    
    template <typename T>
    class get_type
    {
        template <typename T1> static
        typename T1::type test(const typename T1::constraints*);
        template <typename T1> static
        T1 test(...);

    public:
        using type = decltype(test<T>(nullptr));
    };
    
    template <typename T>
    class get_constraints
    {
        template <typename T1> static
        typename T1::constraints test(const typename T1::constraints*);
        template <typename T1> static
        list::list<> test(...);

    public:
        using type = decltype(test<T>(nullptr));
    };
    
    
    
    template <typename TYPE, typename...CONCEPTS> struct
    constrain
    : conceive<typename get_type<TYPE>::type,
               list::join<list::list<CONCEPTS...>, typename get_constraints<TYPE>::type>
      >
    {
    };
    

    
    
    template <typename T> using
    void_t = void;
    
    template <typename...TS> using
    check = void_t<typename std::enable_if<all_true<TS::value...>::value>::type>;


}

#endif /* defined(__FunctionalTemplates__concepts__) */
