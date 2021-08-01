#include "AceLog.h"
#include "LogData.h"

#include <ctime>

USING_NS_ACE;

void AceLog::log(const std::string& msg, Type type)
{
    AceLogPtr pAceLog = std::make_shared<AceLog>();
    pAceLog->msg = msg;
    pAceLog->type = type;
    
    time_t curTime = std::time(NULL);
    tm* pLocal = std::localtime(&curTime);
    
    pAceLog->time = (long long)curTime;
    
    char str[100];
    sprintf(str, "%02d-%02d %02d:%02d:%02d", pLocal->tm_mon + 1, pLocal->tm_mday, pLocal->tm_hour, pLocal->tm_min, pLocal->tm_sec);
    pAceLog->strTime = str;
    
    LogData::getInstance()->addLog(pAceLog);
}
