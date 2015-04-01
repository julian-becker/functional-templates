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
#include <map>
#include <mutex>
#include <string>

namespace
multithreading {
    struct
    message_broker {
        private: std::map<std::string,const std::unique_ptr<i_actor>>
        registry;
        
        private: std::mutex
        mutex;
        
        public:
        message_broker() {}
        
        public: template <typename ACTOR_TYPE, typename...ACTOR_CONSTRUCTOR_ARGS> void
        register_actor(const std::string name,ACTOR_CONSTRUCTOR_ARGS...args) {
            std::lock_guard<std::mutex> lock(mutex);
            registry.emplace(name,std::unique_ptr<i_actor>(new ACTOR_TYPE(*this, args...)));
            registry[name]->run();
        }
        
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
