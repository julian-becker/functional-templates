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

    struct
    i_actor {
        public: virtual void
        notify(message&& msg_in) = 0;
        
        public: virtual void
        run() = 0;

        public: virtual 
        ~i_actor() throw() {}
    };
    
}

#endif
