//
//  actor.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "actor.h"

#include <iostream>
#include <sstream>
#include <map>
#include <memory>

#include <multithreading/broker.h>

using namespace multithreading;


struct
tic_message {};

struct
tic_actor : actor {
    private: std::string
    target;
    
    private: message_broker& broker;
    
    public:
    tic_actor(message_broker& broker, const std::string& target)
    : broker(broker), target(target),
      actor([this](const message& msg) {
        msg.get_dispatcher()
        .handle([&](init_message)   {
            this->broker.post(this->target,tic_message());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            this->notify(init_message());
           // std::this_thread::yield();
        });
      }) {}
    
};


struct
consuming_actor : public actor {
    private: message_broker& broker;
    
    public:
    consuming_actor(message_broker& broker)
    : broker(broker), actor([](const message& msg) {
        static size_t i=0;
        msg.get_dispatcher()
        .handle([](init_message) { std::cout << "consuming_actor: init_message\n";})
        .handle([](tic_message u)   { if(++i%100==0) std::cout << "consuming_actor: tic "<<i<<"\n";})
        .handle([](unsigned u)   { std::cout << "consuming_actor: unsigned: "<<u<<"\n";})
        .handle([](unsigned u,std::string s)   { std::cout << "consuming_actor: unsigned: "<<u<<", string="<<s<<"\n";})
        .handle([](std::function<void(std::string)> f,std::string s)   { f(s); })
        .handle([](int i)        { std::cout << "consuming_actor: int: "<<i<<"\n";})
        .handle([](std::string s){ std::cout << "consuming_actor: std::string: "<<s<<"\n";});
      }) {}
};


int run_playground()
{
    std::shared_ptr<message_broker> broker = std::make_shared<message_broker>();
    broker->register_actor<consuming_actor>("consuming_actor");
    broker->register_actor<tic_actor>("tic_actor","consuming_actor");
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}

