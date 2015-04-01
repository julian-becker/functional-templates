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
    
    class interrupt {
        const std::shared_ptr<std::atomic<bool>>
        is_interrupted;
        
        const std::shared_ptr<std::condition_variable>
        cond;
        
        const std::shared_ptr<std::mutex>
        mutex;

        public:
	interrupt(
            const std::shared_ptr<std::condition_variable> cond,
            const std::shared_ptr<std::atomic<bool>> is_interrupted,
            const std::shared_ptr<std::mutex> mutex)
        : cond(cond),
          is_interrupted(is_interrupted),
          mutex(mutex) {}

        public:
        interrupt(interrupt&& other)
        : cond(std::move(other.cond)),
          is_interrupted(std::move(other.is_interrupted)),
          mutex(std::move(other.mutex)) {}

        public:
        interrupt(const interrupt& other)
        : cond(other.cond),
          is_interrupted(other.is_interrupted),
          mutex(other.mutex) {};

        public:
        ~interrupt() {}

        public: void
        trigger() {
            is_interrupted->store(true);
            cond->notify_all();
        }

        public: bool
        is_triggered () const throw() {
            return is_interrupted->load();
        }
    };
    
    class
    semaphore {
        private: std::atomic<long>
        counter;

        private: std::shared_ptr<std::atomic<bool>>
        is_interrupted;

        private: const std::shared_ptr<std::mutex>
        mutex;

        private: const std::shared_ptr<std::condition_variable>
        cond;

        public:
        semaphore();

        public:
        ~semaphore() throw() {}

        public: void
        wait();

        public: interrupt
        get_interrupt() const { return interrupt(cond,is_interrupted,mutex); }

        public: void
        post() {
                if(!is_interrupted || is_interrupted->load())
                        throw std::make_error_condition(std::errc::io_error);
                std::lock_guard<std::mutex> lock(*mutex);
                counter++;
                cond->notify_one(); // never throws
        }

        public: unsigned long
        load () const {
                return counter.load();
        }
    };

}

#endif /* defined(__FunctionalTemplates__semaphore__) */
