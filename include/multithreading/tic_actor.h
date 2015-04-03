//
//  tic_actor.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 03.04.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__tic_actor__
#define __FunctionalTemplates__tic_actor__

#include <multithreading/actor.h>
#include <multithreading/broker.h>
#include <thread>
#include <multithreading/message.h>

namespace
multithreading {

    /// @brief: An empty message that will be sent by the tic_actor to its broker in regular time intervals
    struct
    tic_message {};

    /// @brief: Actor that generates messages of type 'tic_message' at the specified regular interval
    template <typename INTERVAL_TYPE> struct
    tic_actor : actor {
        private: INTERVAL_TYPE
        duration;
        
        private: size_t
        tic_count;

        private: std::chrono::time_point<std::chrono::steady_clock>
        start_time;
        
        
        /// @brief: constructor for the tic_actor
        /// @param broker:   The broker that manages this actor's lifetime.
        /// @param duration: The time interval between the 'tic_message's that will be generated.
        public:
        tic_actor(message_broker& broker, INTERVAL_TYPE duration)
        : duration(duration), tic_count(static_cast<size_t>(0)),
          actor([this,&broker](const message& msg) {
            msg.get_dispatcher()
            .handle([&broker,this](init_message)   {
                this->start_time = std::chrono::steady_clock::now();
                this->notify(tic_message());
            })
            .handle([&broker,this](tic_message)   {
                std::chrono::time_point<std::chrono::steady_clock> next_tic = start_time + (++tic_count)*this->duration;
                std::this_thread::sleep_until(next_tic);
                broker.notify(tic_message());
                this->notify(tic_message());
            });
          }) {}
    };

}

#endif /* defined(__FunctionalTemplates__tic_actor__) */
