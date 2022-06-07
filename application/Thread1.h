#pragma once 

#include "rtos_thread.h"


class Thread1: public Thread
{
    public:
    using Thread::Thread;
    
    void run(void) override;

    

};