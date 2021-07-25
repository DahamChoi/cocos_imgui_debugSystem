#pragma once

#include "ace.h"
#include "Singleton.h"

#include <base/CCIMEDelegate.h>

NS_ACE_BEGIN

class ImGuiImeDelegate final : public Singleton<ImGuiImeDelegate>, public cocos2d::IMEDelegate
{
    friend class Singleton<ImGuiImeDelegate>;
    
public:
    virtual bool initSingle() override;
    
public:
    virtual bool attachWithIME() override;
    virtual bool detachWithIME() override;
    
    virtual bool canAttachWithIME() override;
    virtual bool canDetachWithIME() override;

public:
    virtual void insertText(const char * text, size_t len) override;
    virtual void deleteBackward() override;
    
public:
    void update();
    
private:
    std::string inputText;
    std::string befText;
    
private:
    ImGuiImeDelegate() = default;
};

NS_ACE_END
