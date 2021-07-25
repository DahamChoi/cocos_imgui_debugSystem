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
        if(ImGui::InputText("", searchInputTextBuf, IM_ARRAYSIZE(searchInputTextBuf), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            onSearchButtonClick();
        }

        ImGui::SameLine();

        if(ImGui::Button("Search"))
        {
            onSearchButtonClick();
        }
    }

    {
        ImGui::Checkbox("DEFAULT", &checkBoxChecked[0]);
        ImGui::SameLine();
        ImGui::Checkbox("WARRNING", &checkBoxChecked[1]);
        ImGui::SameLine();
        ImGui::Checkbox("ERROR", &checkBoxChecked[2]);
    }

    {
        ImGui::BeginChild("Scrolling");

        std::vector<AceLogPtr>& vecLog = LogData::getInstance()->vecLog;
        for(auto& log : vecLog)
        {
            if(log->getType() == AceLog::Type::DEFAULT &&
               false == checkBoxChecked[0])
                continue;
            if(log->getType() == AceLog::Type::WARNING &&
               false == checkBoxChecked[1])
                continue;
            if(log->getType() == AceLog::Type::ERROR &&
               false == checkBoxChecked[2])
                continue;

            auto iter = log->getMsg().find(searchInputTextBuf);
            if(iter != log->getMsg().npos)
            {
                ImGui::Text(log->getMsg().c_str());
            }
        }

        ImGui::EndChild();
    }

    ImGuiObj::end();
}

void DebugLogGui::onSearchButtonClick()
{
    AceLog::log(u8"onSearchButtonClick");
}
