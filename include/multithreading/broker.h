//
//  broker.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 01.04.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__broker__
#define __FunctionalTemplates__broker__


#include <multithreading/i_actor.h>
#include <unordered_map>
#include <mutex>
#include <string>

namespace
multithreading {

    /// @brief: This class serves as a message distributor, reducing the coupling between different actors
    ///         by acting as a broker, i.e. if one actor wants to send a message to another actor, it
    ///         asks the message_broker which has been passed to it during construction to send a message to the specified actor.
    struct
    message_broker {
    
        /// registry for keeping track of all actors
        private: std::unordered_map<std::string,const std::unique_ptr<i_actor>>
        registry;
        
        /// mutex to lock access to all internal data
        private: std::mutex
        mutex;
        
        
        /// @brief: Default constructor
        public:
        message_broker() {}
        
        
        /// @brief: Construct and register an actor of type 'ACTOR_TYPE' under the name 'name'
        ///         using the constructor arguments 'ACTOR_CONSTRUCTOR_ARGS'.
        /// @tparam ACTOR_TYPE: The typename of the actor to be registered and constructed. It is required
        ///                     that this actor accepts a 'message_broker' as first constructor argument.
        public: template <typename ACTOR_TYPE, typename...ACTOR_CONSTRUCTOR_ARGS> void
        register_actor(const std::string name,ACTOR_CONSTRUCTOR_ARGS...args) {
            std::lock_guard<std::mutex> lock(mutex);
            registry.emplace(name,std::unique_ptr<i_actor>(new ACTOR_TYPE(*this, args...)));
            registry[name]->run();
        }
        
        
        /// @brief: Post a message 'msg' of type 'MESSAGE_TYPE' to the actor that has been registered under the
        ///         name 'destination'.
        public: template <typename MESSAGE_TYPE> void
        post(const std::string destination, MESSAGE_TYPE&& msg) {
            std::lock_guard<std::mutex> lock(mutex);
            if(!registry.count(destination))
                throw "unknown actor identifier";
            registry.at(destination)->notify(std::move(msg));
        }
        
        
    };
    
}

#endif /* defined(__FunctionalTemplates__broker__) */
