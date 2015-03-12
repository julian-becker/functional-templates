//
//  actor.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__actor__
#define __FunctionalTemplates__actor__

#include <thread>
#include <exception>
#include <multithreading/message.h>
#include <multithreading/thread_safe_queue.h>

namespace
multithreading {

    class
    actor {
        protected: class init_message{};
        
        private: thread_safe_queue<message>
        incoming_msgs;
        
        /// must be declared after incoming_msgs due to construction order!
        private: semaphore::interrupt&
        interrupt;
        
        private: std::thread
        my_thread;
        
        private: std::exception_ptr
        exception;
        
        
        public:
        actor()
        : interrupt(incoming_msgs.get_interrupt()), my_thread(
            [&]{
                try {
                    notify(message(init_message()));
                    run_actor();
                }
                catch(...) {
                    exception = std::current_exception();
                }
            })
        {}
        
        private: void
        run_actor() {
            while(!interrupt.is_triggered())
                process(incoming_msgs.wait_and_pop());
        };
        
        private: virtual void
        process(const message&) = 0;
        
        public: void
        notify(message&& msg_in) {
            incoming_msgs.push(std::forward<message>(msg_in));
        }
        
        public: virtual
        ~actor() throw () {
            interrupt.trigger();
            my_thread.join();

            // do not rethrow the exception from the destructor
            // if(exception)
            //     std::rethrow_exception(exception);
        }
    };
}

#endif /* defined(__FunctionalTemplates__actor__) */
