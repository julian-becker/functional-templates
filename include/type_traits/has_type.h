//
//  has_type.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 03.11.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#pragma once

template <typename T,typename...Ts> struct
has_type;

template <typename T> struct
has_type<T> {
    static constexpr bool value = false;
};

template <typename T,typename T1, typename...Ts> struct
has_type<T,T1,Ts...> {
    static constexpr bool value = std::is_same<T,T1>::value || has_type<T,Ts...>::value;
};

