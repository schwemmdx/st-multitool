#ifndef _EVENT_HANDLER_H_
#define  EVENT_HANDLER_H_

#define EVNT_H_RUNNING 0
#define EVNT_H_PAUSE 1
#define EVNT_H_RESTART 2 

typedef struct
{
    uint8_t status;
    
}fk_EvntHandler_t;

void fk_EventHandlerInit(fk_EvntHandler_t* pEvnt);

void fk_EvntHandlerTsk(void*);


#endif /* EVENT_HANDLER_H_*/