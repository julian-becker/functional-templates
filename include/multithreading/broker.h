//
//  broker.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 01.04.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__broker__
#define __FunctionalTemplates__broker__


#include <multithreading/actor.h>
#include <unordered_map>
#include <list>
#include <mutex>
#include <string>


namespace
multithreading {

    /// @brief: This class serves as a message distributor, reducing the coupling between different actors
    ///         by acting as a broker, i.e. if one actor wants to send a message to another actor, it
    ///         asks the message_broker which has been passed to it during construction to send a message to the specified actor.
    struct
    message_broker : public actor {
    
        public: template <typename T> struct
        type_wrapper {};
          
        /// registry for keeping track of all actors
        private: std::unordered_map<actor_id,const std::unique_ptr<i_actor>>
        registry;
        
        private: std::list<std::function<void(const message&)>>
        notification_list;
        
        /// mutex to lock access to all internal data
        private: std::mutex
        mutex;
        
        
        /// @brief: Default constructor
        public:
        message_broker() : actor([&](const message& msg){
            /// forward message to each of the registered notifications
            for(auto& entry : this->notification_list)
                entry(msg);
          }) {}
        
        
        /// @brief: Construct and register an actor of type 'ACTOR_TYPE' under the name 'name'
        ///         using the constructor arguments 'ACTOR_CONSTRUCTOR_ARGS'.
        /// @tparam ACTOR_TYPE: The typename of the actor to be registered and constructed. It is required
        ///                     that this actor accepts a 'message_broker' as first constructor argument.
        public: template <typename ACTOR_TYPE, typename...ACTOR_CONSTRUCTOR_ARGS> actor_id
        register_actor(ACTOR_CONSTRUCTOR_ARGS...args) {
            std::unique_ptr<i_actor> new_actor = std::unique_ptr<i_actor>(new ACTOR_TYPE(*this, args...));
            const actor_id new_actor_id = new_actor->get_id();
            std::lock_guard<std::mutex> lock(mutex);
            registry.emplace(new_actor_id,std::move(new_actor));
            registry[new_actor_id]->run();
            return new_actor_id;
        }
        
        
        /// @brief: Post a message 'msg' of type 'MESSAGE_TYPE' to the actor that has been registered under the
        ///         name 'destination'.
        public: template <typename MESSAGE_TYPE> void
        post(const actor_id destination, MESSAGE_TYPE&& msg) {
            std::lock_guard<std::mutex> lock(mutex);
            if(!registry.count(destination))
                throw "unknown actor identifier";
            registry.at(destination)->notify(std::move(msg));
        }
        
        
        /// @brief: Register the actor with id 'target_id' to be informed with a copy of each message
        ///         of type 'MESSAGE_TYPE' that is sent to the broker.
        /// @tparam MESSAGE_TYPE:   The type of the messages that are to be forwarded to the actor with id 'target_id'.
        public: template <typename...MESSAGE_TYPES> void
        register_forwarding(const type_wrapper<MESSAGE_TYPES...>& message_type, const actor_id target_id) {
            std::lock_guard<std::mutex> lock(mutex);
            notification_list.emplace_back([this,target_id](const message& msg){
                msg.get_dispatcher().handle(
                    [this,target_id](MESSAGE_TYPES...msg_content){
                        std::lock_guard<std::mutex> lock(this->mutex);
                        
                        if(registry.count(target_id)) {
                            registry[target_id]->notify(std::move(msg_content)...);
                        }
                    });
            });
        }
        
    };
    
}

#endif /* defined(__FunctionalTemplates__broker__) */
