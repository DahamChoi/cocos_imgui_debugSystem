#include "AceLog.h"
#include "LogData.h"

USING_NS_ACE;

void AceLog::log(const std::string& msg, Type type)
{
    AceLogPtr pAceLog = std::make_shared<AceLog>();
    pAceLog->msg = msg;
    pAceLog->type = type;
    pAceLog->time = 0;
    pAceLog->strTime = "";
    
    LogData::getInstance()->addLog(pAceLog);
}
