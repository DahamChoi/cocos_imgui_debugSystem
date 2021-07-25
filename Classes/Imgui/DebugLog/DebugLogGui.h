//
//  DebugLog.h
//  MPBReboot
//
//  Created by 최다함 on 2021/07/22.
//

#pragma once

#include "ace.h"
#include "ImGuiObj.h"

NS_ACE_BEGIN

class DebugLogGui : public ImGuiObj
{
public:
    DebugLogGui() : ImGuiObj({ 200.f, 200.f }, { 500.f, 500.f })
    {}
    
private:
    char searchInputTextBuf[100] = {'\0', };
    bool checkBoxChecked[3] = { true, true, true };
    
private:
    void onSearchButtonClick();
    
public:
    virtual void update() override;
};

NS_ACE_END
