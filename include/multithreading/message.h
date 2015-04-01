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
            message_wrapper(const TS&...content) = delete;
            virtual ~message_wrapper() throw() {}
        };
        
        public: message_base const * msg;
        
        public: template <typename...TS>
        message(TS&&...content)
        : msg(new message_wrapper<TS...>(std::forward<TS>(content)...))
        {}
        
        message(const message&) = delete;
        
        public:
        message(message&& other)
        : msg(other.msg) {
            other.msg = nullptr;
        }
        
        ~message() throw() {
            if(msg)
                delete msg;
        }
        
        struct
        dispatcher {
            message_base const * msg;

                
            template <typename LAMBDA>
            dispatcher
            handle(LAMBDA handler) const {
                using message_base_type_for_lambda = typename ::callable::callable_traits<LAMBDA>::template arguments<message_wrapper>;
                auto msg_proper = dynamic_cast<const message_base_type_for_lambda*>(msg);
                if(msg_proper) {
                    ::callable::callable<LAMBDA> c(handler);
                    c(msg_proper->content);
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
