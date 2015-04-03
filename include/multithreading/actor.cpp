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
#include <chrono>

#include <multithreading/broker.h>
#include <multithreading/tic_actor.h>

using namespace multithreading;


actor_id multithreading::generate_actor_id() {
    static actor_id id = 0;
    return id++;
}



/// @brief: An example for an actor that listens for a 'tic_message' event on the broker that
///         manages this actor's lifetime.
struct
consuming_actor : public actor {

    /// @brief: constructor
    /// @param broker:  The message broker that manages this actor's lifetime.
    public:
    consuming_actor(message_broker& broker)
    : actor([&broker](const message& msg) {
        static size_t i=0;
        msg.get_dispatcher()
//          .handle([](init_message u) {
//            std::cout << "consuming_actor: init\n";
//        })
        .handle([](tic_message u)   {
            std::cout << "consuming_actor: tic "<<++i<<"\n";
        });
      })
      {
          // register this actor to be informed about all tic_messages that arrive at the broker
          broker.register_forwarding(message_broker::type_wrapper<tic_message>(),get_id());
      }
};

int run_playground()
{
    std::shared_ptr<message_broker> broker = std::make_shared<message_broker>();
    broker->run();
    broker->register_actor<tic_actor<std::chrono::milliseconds>>(std::chrono::milliseconds(1));
    broker->register_actor<consuming_actor>();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}

