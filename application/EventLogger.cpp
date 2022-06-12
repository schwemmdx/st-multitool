
extern "C"
{
    #include "main.h"
    #include "FreeRTOS.h"
    #include "task.h"
}

#include <string>

#include "EventLogger.h"

EventLogger::EventLogger(std::string base_path)
{
    this->logPath = base_path;
    this->sessionFileName = "debug";
    f_open(&this->pLogFile,"log/debug.log",FA_CREATE_ALWAYS | FA_WRITE);
    f_printf(&this->pLogFile,"EventLogger Initialized\n");
    f_close(&this->pLogFile);
}
 void EventLogger::open_logfile()
{
    f_open(&this->pLogFile,"/log/debug.log", FA_OPEN_APPEND |FA_WRITE);
}

void EventLogger::info(std::string infoMsg)
{
  this->typeStamp = "[INFO]";//+this->getTimestamp();
  this->open_logfile();
  f_printf(&this->pLogFile,(this->typeStamp+infoMsg+"\n").c_str());
  f_close(&this->pLogFile);

}


/*
void EventLogger::warn(std::string warnMsg)
{
    logEvent_t evnt;
    evnt.type = LOG_TYPE_WARN;
    evnt.msg = warnMsg+"\n";
    evnt.errc =0;
    this->eventQueue.push(evnt);
}

void EventLogger::err(std::string errMsg)
{
    logEvent_t evnt;
    evnt.type = LOG_TYPE_ERR;
    evnt.msg = errMsg+"\n";
    evnt.errc =0;
    this->eventQueue.push(evnt);
}
*/
std::string EventLogger::getTimestamp()
{
    if(this->useTimeStamp)
    {
        return "[NO_RTC]";
    }
    else
    {
        return "_";
    }
}
