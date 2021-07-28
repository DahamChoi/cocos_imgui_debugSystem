#pragma once

#include "ace.h"

#include "ImGuiObj.h"

NS_ACE_BEGIN

class DebugLogGui : public ImGuiObj
{
public:
    DebugLogGui() : ImGuiObj({ 100.f, 50.f }, { 800.f, 600.f }), comboShowLogCountItems_{ "30", "50", "100", "500", "1000"}
    {}
    
    static const std::string DebugLogGuiKey;
    
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
    
    int searchScrollYCounter_ = 0;
    
    int multLogLimit_ = 1;

    std::string lastSearchedString;
    
    ImVec4 oddColor_ = { 1.f, 1.f, 1.f, 1.f };
    ImVec4 evenColor_ = { 0.8f, 0.8f, 0.8f, 1.f };
    
    int currentSearchResultIdx_;
    int searchResultSize_;
    
private:
    void onSearchButtonClick();
    void onClearButtonClick();
    
    void moveSearchPosition(int capacity);
    
public:
    virtual void update() override;
};

NS_ACE_END

