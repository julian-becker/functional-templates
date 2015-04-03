//
//  i_actor.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 01.04.15.
//  Copyright (c) 2015 Julian Becker. All rights reserved.
//

#ifndef FunctionalTemplates_i_actor_h
#define FunctionalTemplates_i_actor_h

#include <multithreading/message.h>

namespace
multithreading {

    using actor_id = size_t;
    
    /// @brief: abstract actor interfaces
    struct
    i_actor {
    
        /// @brief: Use this member function to send a message to the actor
        public: virtual void
        notify(message&& msg_in) = 0;
        
        /// @brief: This starts the actor thread and brings the actor to life
        public: virtual void
        run() = 0;

        /// @brief: Retrieve the actors id
        public: virtual actor_id
        get_id() const = 0;

        public: virtual
        ~i_actor() throw() {}
    };
    
}

#endif
