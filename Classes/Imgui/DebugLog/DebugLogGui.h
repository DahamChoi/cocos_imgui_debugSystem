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
    DebugLogGui() : ImGuiObj({ 200.f, 200.f }, { 500.f, 500.f }), comboShowLogCountItems_{ "30", "50", "100", "500", "1000"}
    {}
    
private:
    // 검색창
    char inputTextSearchBuf_[100] = {'\0', };
    
    // 필터 체크박스
    bool chkFilterDefault_ = true;
    bool chkFilterWarrning_ = true;
    bool chkFilterError_ = true;
    
    // auto-scroll 체크박스
    bool chkAutoScroll_ = true;
    
    // 로그 갯수 콤보 박스
    int comboShowLogItemCurrentIdx_ = 2;
    const char* comboShowLogCountItems_[5];
    
private:
    int prevLogCount_ = 0;
    
private:
    void onSearchButtonClick();
    void onClearButtonClick();
    
public:
    virtual void update() override;
};

NS_ACE_END
