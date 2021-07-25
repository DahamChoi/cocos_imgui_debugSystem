//
//  ImGuiObj.cpp
//  MPBReboot
//
//  Created by 최다함 on 2021/07/22.
//

#include "ImGuiObj.h"

USING_NS_ACE;

ImGuiObj::ImGuiObj(const ImVec2& windowPos_, const ImVec2& windowSize_)
{
    _windowPos = windowPos_;
    _windowSize = windowSize_;
}

void ImGuiObj::begin(const char * name)
{
    if(_windowPos != DEFAULT_IMVEC2)
    {
        ImGui::SetNextWindowPos(_windowPos, ImGuiCond_FirstUseEver);
    }
    
    if(_windowSize != DEFAULT_IMVEC2)
    {
        ImGui::SetNextWindowSize(_windowSize);
    }
    
    ImGui::Begin(name);
}

void ImGuiObj::end()
{
    ImGui::End();
}

