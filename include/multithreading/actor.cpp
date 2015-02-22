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
#include <map>
#include <memory>

struct
message_broker {
    private: std::map<std::string,const std::unique_ptr<actor>>
    registry;
    
    private: std::mutex
    mutex;
    
    public:
    message_broker() {}
    
    public: template <typename ACTOR_TYPE, typename...ACTOR_CONSTRUCTOR_ARGS> void
    register_actor(const std::string name,ACTOR_CONSTRUCTOR_ARGS...args) {
        std::lock_guard<std::mutex> lock(mutex);
        registry.emplace(name,std::unique_ptr<actor>(new ACTOR_TYPE(*this, args...)));
    }
    
    public: template <typename MESSAGE_TYPE> void
    post(const std::string destination, MESSAGE_TYPE&& msg) {
        std::lock_guard<std::mutex> lock(mutex);
        if(!registry.count(destination))
            throw "unknown actor identifier";
        registry.at(destination)->notify(std::move(msg));
        
    }
};



struct
tic_message {};

struct
tic_actor : actor {
    private: std::string
    target;
    
    private: message_broker& broker;
    
    public:
    tic_actor(message_broker& broker, const std::string& target)
    : broker(broker), target(target) {}
    
    private: virtual void
    process(const message& msg) {
        msg.get_dispatcher()
        .handle([&](init_message)   {
            broker.post(target,tic_message());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            this->notify(init_message());
           // std::this_thread::yield();
        });
    }
};



struct
some_actor : actor {
    private: int
    counter;
    
    private: std::string
    target;
    
    private: message_broker&
    broker;
    
    public:
    some_actor(message_broker& broker, const std::string& target)
    : counter(0), broker(broker), target(target) {}
    
    private: virtual void
    process(const message& msg) {
        msg.get_dispatcher()
        .handle([&](tic_message) {
            if(counter++%100==0) {
                std::cout << "some_actor: tic " << counter << "\n";
                broker.post(target,std::string("message from some_actor"));
                broker.post(target,
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
    private: message_broker& broker;
    
    public:
    consuming_actor(message_broker& broker)
    : broker(broker) {}
    
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
    std::shared_ptr<message_broker> broker = std::make_shared<message_broker>();
    broker->register_actor<consuming_actor>("consuming_actor");
    broker->register_actor<some_actor>("some_actor","consuming_actor");
    broker->register_actor<tic_actor>("tic_actor","some_actor");
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}

