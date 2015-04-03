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

    struct i_actor;
    
    using actor_id = i_actor const *;
    
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
        public: actor_id
        get_id() const { return this; };

        public: virtual
        ~i_actor() throw() {}
    };
    
}

#endif
