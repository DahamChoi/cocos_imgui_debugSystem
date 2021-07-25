//
//  LogData.h
//  MPBReboot
//
//  Created by 최다함 on 2021/07/22.
//

#pragma once

#include "ace.h"

#include "Singleton.h"
#include "AceLog.h"

#include <vector>

NS_ACE_BEGIN

class LogData final : public Singleton<LogData>
{
    friend class Singleton<LogData>;

public:
    std::vector<AceLogPtr> vecLog;
    
public:
    void addLog(const AceLogPtr& pAceLog);
    void clearLog();
    
private:
    LogData() = default;
};

NS_ACE_END
