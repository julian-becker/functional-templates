//
//  semaphore.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__semaphore__
#define __FunctionalTemplates__semaphore__

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <cassert>

namespace
multithreading {

    struct
    interrupt_exception {};

    class
    semaphore {
        public: class
        interrupt;

        private: std::atomic<long>
        counter;

        private: mutable std::mutex
        mutex;

        // must be declared after our mutex due to construction order!
        private: interrupt
        *informed_by;
        
        private: std::condition_variable
        cond;
        
        public:
        semaphore();

        public:
        ~semaphore() throw();
        
        public: void
        wait();
        
        public: interrupt&
        get_interrupt() const { return *informed_by; }
        
        public: void
        post() {
            std::lock_guard<std::mutex> lock(mutex);
            counter++;
            cond.notify_one(); // never throws
        }
        
        public: unsigned long
        load () const {
            return counter.load();
        }
        
    };


    class
    semaphore::interrupt {
        private: std::atomic<bool>
        triggered;

        private: semaphore
        *forward_posts_to;
        
        public:
        interrupt(semaphore *forward_posts_to) : triggered(false), forward_posts_to(forward_posts_to) {
            assert(forward_posts_to);
            std::lock_guard<std::mutex> lock(forward_posts_to->mutex);
            forward_posts_to->informed_by = this;
        }
       
        public: void
        trigger() {
            assert(forward_posts_to);
            std::lock_guard<std::mutex>(forward_posts_to->mutex);
            
            triggered = true;
            forward_posts_to->cond.notify_one(); // never throws
        }

        public: bool
        is_triggered () const throw() {
            return triggered.load();
        }
        
        public: void
        reset () throw() {
            return triggered.store(false);
        }
        
    };

}

#endif /* defined(__FunctionalTemplates__semaphore__) */
