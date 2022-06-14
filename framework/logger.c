
#include "FreeRTOS.h"
#include "task.h"
#include "stdbool.h"
#include "logger.h"


void fk_InitLogger(char* path,fk_Logger_t* pLogger)
{
    pLogger->fs_status = FR_NOT_READY;
    pLogger->logPath = path;

    f_open(&pLogger->logFile,pLogger->logPath,FA_CREATE_ALWAYS| FA_WRITE);
    f_printf(&pLogger->logFile,"Created Logfile\n");
    f_close(&pLogger->logFile);
}

void fkLog_Info(char* infoMsg,fk_Logger_t* pLogger)
{

  f_open(&pLogger->logFile,pLogger->logPath,FA_OPEN_APPEND|FA_WRITE);
  f_printf(&pLogger->logFile,infoMsg);
  f_close(&pLogger->logFile);

}


void log_task (void * params)
{
    while(true)
    {
        vTaskDelay(500);
    }
}