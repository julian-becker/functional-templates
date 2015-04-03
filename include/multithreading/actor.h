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
#include <multithreading/i_actor.h>
#include <multithreading/thread_safe_queue.h>


namespace
multithreading {

    actor_id generate_actor_id();

    /// @brief: Implementation of the i_actor interface. In order to use this class, derive from it and
    ///         provide a behavior in form of a std::function<void(const message&)> to the constructor of actor
    class
    actor : public i_actor {
        protected: class init_message{};

        /// a unique id that can be used to identify each actor instance
        private: actor_id
        id;

        /// pointer to the callable object that constitutes the actual actor behavior
        private: std::function<void(const message&)>
        behavior;


        /// the queue of incoming messages that are to be processed
        private: thread_safe_queue<message>
        incoming_msgs;
        
        /// must be declared after incoming_msgs due to construction order!
        private: interrupt
        interrupt;
        
        /// if any exception is encountered during a call to behavior, it is kept here:
        private: std::exception_ptr
        exception;
        
        /// should be last member to be declared, because it will be initialized with a thread
        /// that may use the other members
        private: std::thread
        my_thread;
        
        
        /// @brief: Constructor for the actor class
        /// @param behavior:  The actual behavior of the actor. This is typically initialized
        ///                   from a lambda expression like the following:
        ///                     [](const message& msg) {
        ///                         msg.get_dispatcher().
        ///                             handle([](int i){ /* handle integer message */ }).
        ///                             handle([](some_type t){ /* handle message t of type some_type */ });
        ///                     }
        protected:
        actor(std::function<void(const message&)> behavior)
        : id(generate_actor_id()), behavior(behavior),
          interrupt(incoming_msgs.get_interrupt()), my_thread()
        {
            notify(message(init_message()));
        }
        
        public: actor_id
        get_id() const override final {
            return id;
        }
        
        
        /// @brief: Start the actor thread.
        ///         Any messages added to the incoming queue via notify() will now get processed.
        public: void
        run() override final {
            my_thread = std::thread([&]{
                try {
                    while(!interrupt.is_triggered()) {
                        message msg(incoming_msgs.wait_and_pop());
                        behavior(std::move(msg));
                    }
                }
                catch(...) {
                    exception = std::current_exception();
                }
            });
        }
        
        
        /// @brief: Send a message to the actor. The message will be enqueued to its incoming queue (FIFO) and
        ///         get processed
        public: void
        notify(message&& msg_in) override final {
            incoming_msgs.push(std::forward<message>(msg_in));
        }
        
        /// @brief: Destructor. This destructor ensures that the actor thread is joined.
        ///         In case the thread is blocked and waiting on the incoming_msgs queue, the interrupt on this queue
        ///         is triggered causing incoming_msgs.wait_and_pop() to unblock
        public: virtual
        ~actor() throw () override {
            interrupt.trigger();
            if(my_thread.joinable())
                my_thread.join();

            // do not rethrow the exception from the destructor
            // if(exception)
            //     std::rethrow_exception(exception);
        }
    };
}

#endif /* defined(__FunctionalTemplates__actor__) */
