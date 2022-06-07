#pragma once 
#include "rtos_thread.h"

#include <queue>

extern "C"
{
    #include "ff.h"
}

#include <string>


#define LOG_TYPE_INFO 0
#define LOG_TYPE_WARN 1
#define LOG_TYPE_ERR 2

typedef struct 
{
    uint8_t type;
    std::string msg;
    uint8_t errc;
}logEvent_t;



class EventLogger
{
    public:
    EventLogger(std::string base_dir);

    void info(std::string);
    void warn(std::string warnMsg);
    void err(std::string errMsg);
    void err(std::string errMsg,int errCode=-1);
    
    private:
    void open_logfile(void);
    std::string typeStamp{"NONE"};
    FIL pLogFile;
    std::string logPath;
    std::string sessionFileName;
    std::string getTimestamp(void);

};