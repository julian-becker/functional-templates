//
//  forth.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 27.02.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#include "forth.h"

#include <demangle.h>
#include <iostream>
#include <meta_types/meta_types.h>
#include <list>
#include <callable/callable.h>
#include <future>
#include <stack>


using namespace words;

template <typename T> void
show() {
    std::cout << demangle<T>() << std::endl;
}

template <typename T> struct make_lazy {
    template <typename IN>
    static auto action(std::future<IN> in) -> std::future<decltype(T::action(std::declval<IN>()))> {
        return std::async([](std::future<IN>&& in1){ return T::action(in1.get()); },std::move(in));
    }
};

struct
compute {
    static auto action(int input) {
        return input*100 + 5;
    }
};

struct
add1 {
    static auto action(int input) {
        return static_cast<double>(input+0.123);
    }
};

template <typename...> struct
bind;

template <> struct
bind<> {
    template <typename T>
    static auto action(T arg) {
        return arg;
    }
};

template <typename F1, typename...REST> struct
bind<F1,REST...> {
    template <typename T>
    static auto action(T arg) {
        return bind<REST...>::action(
                        F1::action(arg)
                    );
    }
};

template <typename...> struct
bind_lazy;

template <> struct
bind_lazy<> {
    template <typename T>
    static auto action(T arg) {
        return arg;
    }
};

template <typename F1, typename...REST> struct
bind_lazy<F1,REST...> {
    template <typename T>
    static auto action(T arg) {
        return bind_lazy<REST...>::action(
                        make_lazy<F1>::action(std::move(arg))
                    );
    }
};


namespace testspace1 {

template <typename...> struct
comp;

template <> struct
comp<> {
    template <typename T>
    static auto action(const std::stack<T>& arg) {
        return arg;
    }

    template <typename T>
    static auto action(std::stack<T>&& arg) {
        return std::forward<std::stack<T>>(arg);
    }
};

template <typename F1, typename...REST> struct
comp<F1,REST...> {

    template <typename T>
    static auto action(const std::stack<T>& arg) {
        return comp<REST...>::action(F1::action(arg));
    }


    template <typename T>
    static auto action(std::stack<T>&& arg) {
        return comp<REST...>::action(F1::action(std::forward<std::stack<T>>(arg)));
    }


    template <typename T>
    static auto action(const T& arg) {
        return comp<REST...>::action(F1::action(std::stack<T>{arg}));
    }
};


struct
dup {
    template <typename T>
    static auto action(std::stack<T> input) {
        input.push(input.top());
        return input;
    }
};


struct
drop {
    template <typename T>
    static auto action(std::stack<T> input) {
        input.pop();
        return input;
    }
};


template <typename...REST> struct
comp<dup,drop,REST...> : comp<REST...> {};
}

void forth_test() {
    using act = bind<compute,add1,add1,compute>;
    using act_lazy = bind_lazy<compute,add1,add1,compute>;
    std::promise<int> p;
    p.set_value(1);
    show<decltype(act_lazy::action(p.get_future()))>();
    auto result_state = act::action(1);
    std::cout << "result=";
    std::cout << result_state;
    std::cout << std::endl;
    std::cout << "result lazy =";
    std::cout << act_lazy::action(p.get_future()).get();
    std::cout << std::endl;
    

    using act1 = testspace1::comp<testspace1::dup,testspace1::drop,testspace1::dup,testspace1::drop>;
    std::stack<int> s;
    s.push(7);
    auto result_state1 = act1::action(s);
    std::cout << "result=";
    while(!result_state1.empty())
        std::cout << result_state1.top() << " ", result_state1.pop();
    std::cout << std::endl;
    
    using resT = eval_t<word<quote<dup>,quote<>,cons>>;
    show<resT>();

    using resT2 = eval_t<word<int_<42>,succ,succ,pred,succ > >;
    show<resT2>();

    using resT3 = eval_t<word<int_<2>,pred,pred,null > >;
    show<resT3>();

    using resT4 = eval_t<word<quote<bool_<true>>,quote<int_<1337>,dup>,quote<int_<31>>,ifte > >;
    show<resT4>();

    using resT5 = eval_t<word<int_<0>,quote<null>,quote<succ>,quote<dup,pred,multiply>,ifte>>;
    show<resT5>();

    using resT6 = eval_t<word<int_<6>,fac>>; // -> stack<value_type<int,720>>
    show<resT6>();
    
    using resT7 = eval_t<word<int_<3>,int_<7>,quote<int_<11>,multiply>,app2>>;
    show<resT7>();
    
    using resT8 = eval_t<word<int_<3>,int_<2>,equal>>;
    show<resT8>();
    
    using resT9 = eval_t<word<int_<5>,fib2>>;
    show<resT9>();
    
    using resT10 = eval_t<word<quote<int_<1>,int_<2>>,quote<int_<3>,int_<4>>,concat>>;
    show<resT10>();
    
}

