    //
    //  playground.cpp
    //  FunctionalTemplates
    //
    //  Created by Julian Becker on 08.11.14.
    //  Copyright (c) 2014 Julian Becker. All rights reserved.
    //

    #include "playground.h"
    #include <list/length.h>
    #include <list/join_n.h>
    #include <tuple>
    #include <callable.h>



    #include <iostream>
    #include <functional>
    #include <memory>
    #include <unordered_map>
    #include <type_traits>

    template <typename BASE>
    struct
    Factory {
        private: using
        TCloneFn = std::function<std::shared_ptr<BASE>(BASE const * const)>;
        
        private:
        static std::unordered_map<BASE const*,TCloneFn> cloneFnMap;
        
        public: template <typename DERIVED_TYPE, typename...TS>
        static std::shared_ptr<BASE>
        create(TS...args) {
            const std::shared_ptr<BASE> pNewObj =
                std::shared_ptr<BASE>(
                    new DERIVED_TYPE(args...),
                    [&](BASE* p){
                        cloneFnMap.erase(p);
                        delete p;
                    }
                );
            
            cloneFnMap[pNewObj.get()] = [&](BASE const * const orig){
                return create<DERIVED_TYPE>(std::ref(static_cast<DERIVED_TYPE const &>(*orig)));
            };
            return pNewObj;
        }
        
        public: static std::shared_ptr<BASE>
        clone(std::shared_ptr<BASE const> original) {
            return cloneFnMap[original.get()](original.get());
        }
    };

    template <typename BASE> std::unordered_map<BASE const*,typename Factory<BASE>::TCloneFn> Factory<BASE>::cloneFnMap;

    class Base {
        public: virtual ~Base() throw() {}
        public: virtual void whoAmI() const {
            std::cout << "I am Base instance " << this << "\n";
        }
    };


    class Derived : public Base {
        std::string name;
        public: Derived(std::string name) : name(name) {}
        public: Derived(const Derived&other) : name("copy of "+other.name) {
        }
        private: virtual void whoAmI() const {
            std::cout << "I am Derived instance " << this << " " << name << "\n";
        }
    };

#include <thread>
#include <setjmp.h>
#include <exception>

struct wrapper_factor
{
    template<class F>
    struct wrapper
    {
        static_assert(std::is_empty<F>(), "Lambdas must be empty");
        template<class... Ts>
        auto operator()(Ts&&... xs) const -> decltype(reinterpret_cast<const F&>(*this)(std::forward<Ts>(xs)...))
        {
            return reinterpret_cast<const F&>(*this)(std::forward<Ts>(xs)...);
        }
    };

    template<class F>
    constexpr wrapper<F> operator += (F*) const
    {
        return {};
    }
};

struct addr_add
{
    template<class T>
    friend typename std::remove_reference<T>::type *operator+(addr_add, T &&t) 
    {
        return &t;
    }
};

#define STATIC_LAMBDA wrapper_factor() += true ? nullptr : addr_add() + []

const constexpr auto add_one = STATIC_LAMBDA(int x)
{
    return x + 1;
};

#include <vector>




template <typename T, T val> struct someval {
    using type = T;
    static constexpr T value = val;
};




