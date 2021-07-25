#pragma once

#include "ace.h"

NS_ACE_BEGIN

class AceLog
{
public:
    enum class Type
    {
        DEFAULT,
        WARNING,
        ERROR
    };
    
private:
    Type type;
    std::string msg;
    long long time;
    std::string strTime;
    
public:
    Type getType() const { return type; }
    std::string getMsg() const { return msg; }
    long long getTime() const { return time; }
    std::string getStrTime() const { return strTime; }
    
public:
    static void log(const std::string& msg, Type type = Type::DEFAULT);
};

using AceLogPtr = std::shared_ptr<AceLog>;

NS_ACE_END
