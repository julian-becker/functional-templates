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



    #include <iostream>
    #include <functional>
    #include <memory>
    #include <unordered_map>

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
    #include <exception>>

    static jmp_buf buf;

    void my_terminate() {
        std::cout << "caught terminate \n";
        longjmp(buf,1);
    }

    void kill_thread(std::thread* t) {
        std::set_terminate(&my_terminate);
        
        if ( !setjmp(buf) ) {
       //     t.detach();
            delete t;
        }
    }
/*
    void run_playground() {
        std::shared_ptr<Base> p1 = Factory<Base>::create<Derived>("Original");
        std::shared_ptr<Base> p2 = Factory<Base>::clone(p1);
        std::shared_ptr<Base> p3 = Factory<Base>::clone(p2);
        p1->whoAmI();
        p2->whoAmI();
        p3->whoAmI();
        std::set_terminate(&my_terminate);
        std::thread* t = new std::thread([]{ while(1)
            std::cout << ".";
            });
        kill_thread(t);
        std::cout << "done\n";
        
        while(1);
    }
*/


