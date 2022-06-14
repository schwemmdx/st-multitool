
#include "event_handler.h"


#include "FreeRTOS.h"
#include "task.h"

void fk_EvntHandlerTsk(void* param)
{

    fk_EvntHandler_t* pEvnt = (fk_EvntHandler_t*) param;

    while(pEvnt->status == EVNT_H_RUNNING)
    {

        // Do shit 

        
        vTaskDelay(500);
    }
}