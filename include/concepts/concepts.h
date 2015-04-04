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

    /// helper meta-function to check if all given arguments are true
    template <bool...> struct
    all_true;

    /// helper meta-function to check if all given arguments are true
    template <> struct
    all_true<> {
        /// Return value: true for the fallback case
        static constexpr bool
        value = true;
    };
    
    /// recursive specialization of 'all_true'
    template <bool b,bool...rest> struct
    all_true<b,rest...> {
        /// Return value: Will be true if all given template arguments are true.
        static constexpr bool
        value = b && all_true<rest...>::value;
    };
    
    
    /// @brief: This metafunction can be used to verify if 'TYPE' meets the requirements of the concepts
    ///         listed in 'CONCEPT_LIST'.
    ///         If the type does not meet one ore more concept requirements, the static_asert will complain.
    template <typename TYPE, typename CONCEPT_LIST> struct
    check_concept;
    
    /// specialization of 'check_concepts'
    template <typename TYPE, typename...CONCEPTS> struct
    check_concept<TYPE,list::list<CONCEPTS...>> {
        /// the list of constraints
        using
        constraints = list::list<CONCEPTS...>;
        
        /// helper function to verify if the type fulfills its concept requirements
        template<typename T> struct
        apply {
            /// the return value will be true if the type fulfills its requirements
            static constexpr bool
            value = all_true<CONCEPTS::template apply<TYPE>::value...>::value;
        };
        
        /// the unconstrained, bare type
        using
        type = TYPE;
        
        /// the value will be true if the type fulfills its requirements.
        static constexpr bool
        value =apply<TYPE>::value;
        
        static_assert(value,"invalid concept instantiation");
    };
    
    
    /// @brief: Retrieve the actual type from a constrained type 'T'.
    template <typename T>
    class get_type {
        /// If the type 'T1' is already constrained, it has a static member 'constraints'. In this case
        /// return the member 'type'.
        template <typename T1> static
        typename T1::type
        test(const typename T1::constraints*);
        
        /// If the type 'T1' is still unconstrained, just return 'T1'.
        template <typename T1> static
        T1 test(...);

    public:
        using type = decltype(test<T>(nullptr));
    };
    
    /// convenience wrapper for get_type<T>::type
    template <typename T> using
    get_type_t = typename get_type<T>::type;
    
    
    /// @brief: Retrive the list of constraints from a possibly constrained type. If the type is unconstrained, the list will be empty.
    /// @tparam T: The type from which the list of constraints is requested.
    template <typename T>
    class get_constraints {
        /// If the type is already constrained, return the list of constraints.
        template <typename T1> static typename T1::constraints
        test(const typename T1::constraints*);
        
        /// If the type is still unconstrained, return an empty list.
        template <typename T1> static list::list<>
        test(...);

    public:
        /// The list of constraints for the type 'T'
        using type = decltype(test<T>(nullptr));
    };
    
    
    /// @brief: Enforce constraints 'CONCEPTS' for the type 'TYPE'.
    ///         E.g. 'using signed_type = constrain<signed int, Signed>;' will compile, but
    ///         this 'using sgn = constrain<unsigned, Signed>;' will not compile.
    /// @tparam TYPE:   The type which shall be constrained.
    /// @tparam CONCEPTS: The list of concepts to enforce for the 'TYPE'.
    template <typename TYPE, typename...CONCEPTS> struct
    constrain
    : check_concept<typename get_type<TYPE>::type,
               list::join<list::list<CONCEPTS...>, typename get_constraints<TYPE>::type>
      >
    {
    };
    
    
    /// @brief: Convenience wrapper for 'constrain<T,CONCEPTS...>::type', that allows using a type
    ///         but ensuring it has the desired properties in one place.
    template <typename T,typename...CONCEPTS> using
    constrain_t = typename constrain<T,CONCEPTS...>::type;
    

    
    /// @brief: Makes an unconstrained bare type 'T' constrained with an empty list of constraints.
    /// @tparam T: The type which is possibly unconstrained.
    template <typename T> class
    ensure_constrained {
        /// If the type is already constrained, return the type 'T1'.
        template <typename T1> static T1
        test(const typename T1::constraints*);
        
        /// If the type is still unconstrained, make it constrained
        template <typename T1> static constrain<T1>
        test(...);

    public:
        /// The constrained type that now has members 'value', 'type', and 'constraints' etc.
        using type = decltype(test<T>(nullptr));
    };
    
    
    /// convenience wrapper for typename ensure_constrained<T>::type.
    template <typename T> using
    ensure_constrained_t = typename ensure_constrained<T>::type;
    
    /// Use this for SFINAE in order to ensure that all types fulfill their concept requirements
    /// E.g.
    ///     template <
    ///         typename T,
    ///         typename = check<constrain<T,Signed>
    ///     > struct
    ///     accepts_only_signed_type {}
    template <typename...TS> using
    check = std::enable_if_t<all_true<ensure_constrained_t<TS>::value...>::value>;


}

#endif /* defined(__FunctionalTemplates__concepts__) */
