//
//  message.h
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#ifndef __FunctionalTemplates__message__
#define __FunctionalTemplates__message__


#include <tuple>
#include <type_traits>
#include <callable/callable.h>

namespace
multithreading {

    struct
    message {
        private: struct
        message_base {
            virtual ~message_base() throw() {}
        };

        private: template <typename...TS> struct
        message_wrapper : message_base {
            const std::tuple<TS...> content;
            explicit message_wrapper(TS&&...content) : content{std::forward<TS>(content)...} {}
//            explicit message_wrapper(std::add_lvalue_reference_t<TS>...content) : content{std::forward<TS>(content)...} {}
            virtual ~message_wrapper() throw() {}
        };
        
        /// pointer to the actual message
        public: message_base const *
        msg;
        
        /// construct a message containing all the arguments listed in 'content'
        public: template <typename...TS>
        message(TS&&...content)
        : msg(new message_wrapper<TS...>(std::forward<TS>(content)...))
        {
        }
        
        /// messages are not copyable. They can only be moved
        message(const message&) = delete;
        
        /// move constructor. Since messages are not copyable, we have to provide this such that
        /// messages can be moved from sender to the receiver.
        public:
        message(message&& other)
        : msg(other.msg) {
            other.msg = nullptr;
        }
        
        /// destructor. Will delete the message content if the message has not been moved from.
        ~message() throw() {
            if(msg)
                delete msg;
        }
        
        
        /// @brief: This struct is a utility that allows switching behavior based on the type of message content without using dynamic_cast-like consturcts.
        ///         This can be used e.g. like this:
        ///             message msg(/*some content*/);
        ///             msg.get_dispatcher()
        ///             .handle([](int i) { /*this will be executed if message contains an int*/ })
        ///             .handle([](double d) { /*executed if message contains an double*/ })
        ///             .handle([](std::string) { /*executed if message contains an std::string*/ });
        struct
        dispatcher {
            /// pointer to the message content
            message_base const* msg;

            /// @brief: This calls the 'handler' if its argument is of the same type as the content of the message pointed to by 'msg'.
            template <typename LAMBDA>
            dispatcher
            handle(LAMBDA handler) const {
                // this will make 'message_base_type_for_lambda' the type 'message_wrapper</*list of types the 'LAMBDA' accepts as arguments*/>'.
                using message_base_type_for_lambda = typename ::callable::callable_traits<LAMBDA>::template arguments<message_wrapper>;
                
                // check if the message content can be handled by the 'handler'
                auto msg_proper = dynamic_cast<message_base_type_for_lambda const *>(msg);
                if(msg_proper) {
                    // it can be handled, thus call the handler with the message content
                    ::callable::callable<LAMBDA> call_delegator(handler);
                    call_delegator(msg_proper->content);
                }
                return dispatcher{msg};
            }
        };
        
        dispatcher get_dispatcher() const {
            return dispatcher{msg};
        }
    };

}

#endif /* defined(__FunctionalTemplates__message__) */
