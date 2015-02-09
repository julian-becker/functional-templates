//
//  actor.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "actor.h"

#include <iostream>

using namespace multithreading;


#include <sstream>

struct
tic_message {};

struct
tic_actor : actor {
    private: std::shared_ptr<actor>
    target;
    
    public:
    tic_actor(const std::shared_ptr<actor>& target)
    : target(target) {}
    
    private: virtual void
    process(const message& msg) {
        msg.get_dispatcher()
        .handle([&](init_message)   {
            target->notify(tic_message());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            this->notify(init_message());
           // std::this_thread::yield();
        });
    }
};



struct
some_actor : actor {
    private: int counter;
    private: std::shared_ptr<actor>
    target;
    
    public:
    some_actor(const std::shared_ptr<actor>& target)
    : counter(0), target(target) {}
    
    private: virtual void
    process(const message& msg) {
        msg.get_dispatcher()
        .handle([&](tic_message) {
            if(counter++%100==0) {
                std::cout << "some_actor: tic " << counter << "\n";
                target->notify(std::string("message from some_actor"));
                target->notify(
                    message(
                        std::function<void(std::string)>([](std::string s){ std::cout << "handling string s="<<s<<"\n"; }),
                        std::string("message from some_actor")
                    )
                );
            }
        });
    }
};

struct
consuming_actor : actor {
    private: virtual void
    process(const message& msg) {
        msg.get_dispatcher()
        .handle([](init_message) { std::cout << "consuming_actor: init_message\n";})
        .handle([](unsigned u)   { std::cout << "consuming_actor: unsigned: "<<u<<"\n";})
        .handle([](unsigned u,std::string s)   { std::cout << "consuming_actor: unsigned: "<<u<<", string="<<s<<"\n";})
        .handle([](std::function<void(std::string)> f,std::string s)   { f(s); })
        .handle([](int i)        { std::cout << "consuming_actor: int: "<<i<<"\n";})
        .handle([](std::string s){ std::cout << "consuming_actor: std::string: "<<s<<"\n";});
    }
};

int run_playground()
{
    std::shared_ptr<actor> receptor = std::shared_ptr<actor>(new consuming_actor);
    std::shared_ptr<actor> some = std::shared_ptr<actor>(new some_actor(receptor));
    std::shared_ptr<actor> clock = std::shared_ptr<actor>(new tic_actor(some));
    std::this_thread::sleep_for(std::chrono::seconds(20));
    return 0;
}
