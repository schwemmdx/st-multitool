#pragma once 

#include "rtos_thread.h"


class Thread2: public Thread
{
    public:
    using Thread::Thread;
    
    void run(void) override;

    

};