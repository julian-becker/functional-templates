//
//  semaphore.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "semaphore.h"

using namespace multithreading;

semaphore::semaphore()  : counter(0L), informed_by(new interrupt(this)) {}

// must be declared here because otherwise semaphore::interrupt is an incomplete type
semaphore::~semaphore() throw()  {
    delete informed_by;
}

void
semaphore::wait() {
    std::unique_lock<std::mutex> lock(mutex);
    if(0L==counter) {
        cond.wait(lock,[&]{
            if(informed_by->is_triggered())
                throw interrupt_exception();
            return counter>0;
        });
    }
    counter--;
}

