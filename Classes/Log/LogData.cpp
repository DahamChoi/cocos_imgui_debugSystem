#include "LogData.h"

USING_NS_ACE;

void LogData::addLog(const AceLogPtr& pAceLog)
{
    vecLog.push_back(pAceLog);
}

void LogData::clearLog()
{
    vecLog.clear();
}
