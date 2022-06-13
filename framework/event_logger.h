#ifndef _EVENT_LOGGER_H_
#define _EVENT_LOGGER_H_

#include <stdbool.h>
#include "ff.h"



typedef struct 
{
    FRESULT fs_status;
    uint8_t type;
    char msg[20];
    int err;
    char* logPath;
    char sessionFileName[10];
    FIL logFile;
    
}fk_Logger_t;



void fk_InitLogger(char* path,fk_Logger_t* pLogger);  
void fk_LogInfo(char* infoMsg,fk_Logger_t* pLogger);
void fk_LogWarn(char* warnMsg);
void fk_LogErr(char* errMsg);
void fk_LoglinkRTC(void* pRTC);
void fk_LogTask(void);


#endif /*_EVENT_LOGGER_H_*/