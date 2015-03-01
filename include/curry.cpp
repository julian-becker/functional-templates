#include <curry.h>
#include <result_of.h>
#include <meta_types/meta_types.h>
#include <callable/callable.h>


#include <chrono>


template<typename N1, typename N2, typename...S> struct
curry_test_fn_builder : curry_test_fn_builder<N1, meta_types::dec<N2>, meta_types::dec<N2>, S...> {
};

template<typename N, typename...S> struct
curry_test_fn_builder<N,N,S...> {
    std::tuple<typename S::type...> args_copy;
    void operator() (typename S::type ... args) {
        args_copy = std::tuple<typename S::type...>(args...); /// do something with args to prevent optimization
    }
};

template <int N> using
curry_test_fn = curry_test_fn_builder<meta_types::int_<0>,meta_types::int_<N>>;

#include <iostream>

void test_curry() {
    unsigned N=1000000;
    {
        constexpr unsigned n=1;
        curry_test_fn<n> t1;
        auto curried = curry(t1);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t1(1);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=2;
        curry_test_fn<n> t2;
        auto curried = curry(t2);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t2(1,2);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=3;
        curry_test_fn<n> t3;
        auto curried = curry(t3);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t3(1,2,3);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=4;
        curry_test_fn<n> t4;
        auto curried = curry(t4);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t4(1,2,3,4);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=5;
        curry_test_fn<n> t5;
        auto curried = curry(t5);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t5(1,2,3,4,5);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=6;
        curry_test_fn<n> t6;
        auto curried = curry(t6);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5)(6);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t6(1,2,3,4,5,6);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=7;
        curry_test_fn<n> t7;
        auto curried = curry(t7);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5)(6)(7);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t7(1,2,3,4,5,6,7);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=8;
        curry_test_fn<n> t8;
        auto curried = curry(t8);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5)(6)(7)(8);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t8(1,2,3,4,5,6,7,8);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=9;
        curry_test_fn<n> t9;
        auto curried = curry(t9);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5)(6)(7)(8)(9);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t9(1,2,3,4,5,6,7,8,9);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=10;
        curry_test_fn<n> t10;
        auto curried = curry(t10);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5)(6)(7)(8)(9)(10);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t10(1,2,3,4,5,6,7,8,9,10);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=11;
        curry_test_fn<n> t;
        auto curried = curry(t);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5)(6)(7)(8)(9)(10)(11);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t(1,2,3,4,5,6,7,8,9,10,11);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=12;
        curry_test_fn<n> t;
        auto curried = curry(t);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5)(6)(7)(8)(9)(10)(11)(12);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t(1,2,3,4,5,6,7,8,9,10,11,12);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=13;
        curry_test_fn<n> t;
        auto curried = curry(t);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5)(6)(7)(8)(9)(10)(11)(12)(13);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t(1,2,3,4,5,6,7,8,9,10,11,12,13);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=14;
        curry_test_fn<n> t;
        auto curried = curry(t);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5)(6)(7)(8)(9)(10)(11)(12)(13)(14);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t(1,2,3,4,5,6,7,8,9,10,11,12,13,14);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
    {
        constexpr unsigned n=15;
        curry_test_fn<n> t;
        auto curried = curry(t);
        auto start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            curried(1)(2)(3)(4)(5)(6)(7)(8)(9)(10)(11)(12)(13)(14)(15);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        start = std::chrono::system_clock::now();
        for(size_t i=0; i<N; i++)
            t(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
        auto duration_normal = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start);
        std::cout << "N="<<N<<", n="<<n<<", duration="<<duration.count()<<", duration_normal="<<duration_normal.count()<<", overhead="<<((double)duration.count()/(double)duration_normal.count())/n<<"\n";
    }
}