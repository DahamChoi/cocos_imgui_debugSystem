//
//  DebugLog.cpp
//  MPBReboot
//
//  Created by 최다함 on 2021/07/22.
//

#include "DebugLogGui.h"
#include "LogData.h"
#include "AceLog.h"

USING_NS_ACE;

void DebugLogGui::update()
{
    ImGuiObj::begin("DEBUG LOG");

    {
        if(ImGui::InputText("검색창", inputTextSearchBuf_, IM_ARRAYSIZE(inputTextSearchBuf_), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            onSearchButtonClick();
        }
    }
    
    {
        ImGui::Combo("로그갯수", &comboShowLogItemCurrentIdx_, comboShowLogCountItems_, IM_ARRAYSIZE(comboShowLogCountItems_));
    }

    {
        ImGui::Checkbox("DEFAULT", &chkFilterDefault_);
        ImGui::SameLine();
        ImGui::Checkbox("WARRNING", &chkFilterWarrning_);
        ImGui::SameLine();
        ImGui::Checkbox("ERROR", &chkFilterError_);
        
        ImGui::SameLine();
        ImGui::Checkbox("자동스크롤", &chkAutoScroll_);
        
        ImGui::SameLine();
        
        if(ImGui::Button("모든로그삭제"))
        {
            onClearButtonClick();
        }
    }

    {
        ImGui::BeginChild("Scrolling");
        
        int logLimit = atoi(comboShowLogCountItems_[comboShowLogItemCurrentIdx_]);
        std::vector<AceLogPtr>& vecLog = LogData::getInstance()->vecLog;
        
        for(int idx = std::max(0, (int)vecLog.size() - logLimit); idx < (int)vecLog.size(); idx++)
        {
            AceLogPtr& log = vecLog[idx];
            
            if(log->getType() == AceLog::Type::DEFAULT &&
               false == chkFilterDefault_)
                continue;
            if(log->getType() == AceLog::Type::WARNING &&
               false == chkFilterWarrning_)
                continue;
            if(log->getType() == AceLog::Type::ERROR &&
               false == chkFilterError_)
                continue;

//            auto iter = log->getMsg().find(inputTextSearchBuf_);
//            if(iter != std::string::npos)
//            {
//                ImGui::Text("%s", log->getMsg().c_str());
//             }
            ImGui::Text("%s", log->getMsg().c_str());
        }
        
        if(prevLogCount_ != (int)vecLog.size() && true == chkAutoScroll_)
        {
            ImGui::SetScrollY(ImGui::GetScrollMaxY());
        }
        prevLogCount_ = (int)vecLog.size();

        ImGui::EndChild();
    }

    ImGuiObj::end();
}

void DebugLogGui::onSearchButtonClick()
{
    AceLog::log(u8"onSearchButtonClick");
}

void DebugLogGui::onClearButtonClick()
{
    LogData::getInstance()->clearLog();
}
