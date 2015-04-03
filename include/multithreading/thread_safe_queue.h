//
//  thread_safe_queue.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__thread_safe_queue__
#define __FunctionalTemplates__thread_safe_queue__

#include <queue>
#include <multithreading/semaphore.h>

namespace multithreading {

    template <typename message> class
    thread_safe_queue {
        private: std::queue<message>
        queue;
        
        private: std::mutex
        mutex;
        
        private: semaphore
        new_msg_notification;
        
        public: void
        push(message&& msg) {
            {
                std::lock_guard<std::mutex> lock(mutex);
                queue.push(std::move(msg));
            }
            new_msg_notification.post();
        }
        
        public: message
        wait_and_pop() {
            new_msg_notification.wait();
            std::lock_guard<std::mutex> lock(mutex);
            auto msg(std::move(queue.front()));
            queue.pop();
            return msg;
        }
        
        public: interrupt
        get_interrupt() const { return new_msg_notification.get_interrupt(); }
    };
}

#endif /* defined(__FunctionalTemplates__thread_safe_queue__) */
