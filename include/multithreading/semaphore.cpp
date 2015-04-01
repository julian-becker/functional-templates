//
//  semaphore.cpp
//  FunctionalTemplates
//
//  Created by Julian Becker on 10.12.14.
//  Copyright (c) 2014 Julian Becker. All rights reserved.
//

#include "semaphore.h"

using namespace multithreading;

semaphore::semaphore()
: counter(0L),
  is_interrupted(new std::atomic<bool>(false)),
  cond(new std::condition_variable),
  mutex(new std::mutex) {}

void
semaphore::wait() {
    std::unique_lock<std::mutex> lock(*mutex);
    if(0L==counter && !is_interrupted->load() && cond) {
        cond->wait(lock,[&]{
                if(is_interrupted->load())
                        throw interrupt_exception();
                return counter>0;
        });
    }
    counter--;
}

