#include "DebugLogGui.h"
#include "LogData.h"
#include "AceLog.h"
#include "ImguiManager.h"

USING_NS_ACE

const std::string DebugLogGui::DebugLogGuiKey = "DebugLog";

void DebugLogGui::update()
{
    {
        ImGui::SetNextWindowPos(_windowPos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(_windowSize, ImGuiCond_FirstUseEver);
    }
    
    ImGuiObj::begin("DEBUG LOG");

    {
        ImGui::SetNextItemWidth(80.f);
        if(ImGui::Combo("##combo", &comboShowLogItemCurrentIdx_, comboShowLogCountItems_, IM_ARRAYSIZE(comboShowLogCountItems_)))
        {
            multLogLimit_ = 1;
        }
        
        ImGui::SameLine();
        
        if(ImGui::InputText("##input", inputTextSearchBuf_, IM_ARRAYSIZE(inputTextSearchBuf_), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            onSearchButtonClick();
        }
        
        ImGui::SameLine();
        
        if(ImGui::Button(" 검색 "))
        {
            onSearchButtonClick();
        }
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
        
        ImGui::SameLine();
        
        if(ImGui::Button("  창 닫기  "))
        {
            ImguiManager::getInstance()->removeImGui(DebugLogGui::DebugLogGuiKey);
        }
    }
    
    if(false == lastSearchedString.empty())
    {
        if(searchResultSize_ <= 0)
        {
            ImGui::TextColored(ImColor(255, 0, 0), "%s에 대한 검색결과가 없습니다!", lastSearchedString.c_str());
        }
        else
        {
            ImGui::Text("%s에 대한 검색결과 : %d개의 로그를 찾았습니다. ( %d / %d )", lastSearchedString.c_str(), searchResultSize_, currentSearchResultIdx_ + 1, searchResultSize_);
            
            ImGui::SameLine();
            
            if(ImGui::Button("PREV"))
            {
                moveSearchPosition(-1);
            }
            
            ImGui::SameLine();
            
            if(ImGui::Button("NEXT"))
            {
                moveSearchPosition(1);
            }
        }
    }

    {
        ImGui::BeginChild("Scrolling");
        
        int selectedLogLimit = atoi(comboShowLogCountItems_[comboShowLogItemCurrentIdx_]);
        int logLimit = selectedLogLimit * multLogLimit_;
        std::vector<AceLogPtr>& vecLog = LogData::getInstance()->vecLog;
        
        std::vector<std::pair<AceLogPtr, int>> vecFilteredLog;
        for(int idx = (int)vecLog.size() - 1; idx >= 0; idx--)
        {
            AceLogPtr& log = vecLog[idx];
            
            if(log->getType() == AceLog::Type::DEFAULT && false == chkFilterDefault_)
                continue;
            if(log->getType() == AceLog::Type::WARNING && false == chkFilterWarrning_)
                continue;
            if(log->getType() == AceLog::Type::ERROR && false == chkFilterError_)
                continue;
            
            vecFilteredLog.push_back({ log, idx });
            if((int)vecFilteredLog.size() >= logLimit)
                break;
        }
        
        int counter = 0, searchCounter = 0;
        for(auto iter = vecFilteredLog.rbegin(); iter != vecFilteredLog.rend(); iter++, counter++)
        {
            ImVec4 textColor = (counter % 2 == 0) ? evenColor_ : oddColor_;
            
            if(false == lastSearchedString.empty() && iter->first->getMsg().find(lastSearchedString) != std::string::npos)
            {
                textColor = ImColor(255, 0, 0);
                if(searchCounter++ == currentSearchResultIdx_)
                {
                    float textLineHeight = ImGui::GetTextLineHeight();
                    float nextPosY = counter * textLineHeight;
                    
                    if(searchScrollYCounter_++ <= 2)
                    {
                        ImGui::SetScrollY(nextPosY);
                    }
                    
                    textColor = ImColor(255, 100, 0);
                }
            }

            ImGui::TextColored(textColor, "%s - %s", iter->first->getStrTime().c_str(), iter->first->getMsg().c_str());
        }
        
        searchResultSize_ = searchCounter;
        
        if(prevLogCount_ != (int)vecLog.size() && true == chkAutoScroll_)
        {
            ImGui::SetScrollY(ImGui::GetScrollMaxY());
        }
        prevLogCount_ = (int)vecLog.size();

        {
            ImVec2 mouse_delta = ImGui::GetIO().MouseDelta;
            ScrollWhenDraggingOnVoid(ImVec2(0.0f, -mouse_delta.y), "Scrolling");
            if(ImGui::GetScrollY() == 0.f && mouse_delta.y < 0.f && logLimit < vecLog.size())
            {
                multLogLimit_ += 1;
                
                int newLogLimit = std::min((int)vecLog.size(), selectedLogLimit * multLogLimit_);
                
                float textLineHeight = ImGui::GetTextLineHeight();
                ImGui::SetScrollY(textLineHeight * (newLogLimit - logLimit));
            }
        }
        
        ImGui::EndChild();
    }

    ImGuiObj::end();
}

void DebugLogGui::onSearchButtonClick()
{
    if(lastSearchedString == inputTextSearchBuf_)
    {
        moveSearchPosition(1);
        return;
    }
    
    chkAutoScroll_ = false;
    currentSearchResultIdx_ = 0;
    searchScrollYCounter_ = 0;
    lastSearchedString = inputTextSearchBuf_;
}

void DebugLogGui::onClearButtonClick()
{
    LogData::getInstance()->clearLog();
}

void DebugLogGui::moveSearchPosition(int capacity)
{
    currentSearchResultIdx_ += capacity;
    if(currentSearchResultIdx_ >= searchResultSize_)
    {
        currentSearchResultIdx_ = 0;
    }
    else if(currentSearchResultIdx_ < 0)
    {
        currentSearchResultIdx_ = searchResultSize_ - 1;
    }
    
    searchScrollYCounter_ = 0;
}
