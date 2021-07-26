//
//  ImGuiObj.h
//  MPBReboot
//
//  Created by 최다함 on 2021/07/22.
//

#pragma once

#include "imgui.h"

#include "ace.h"

#include <memory>

NS_ACE_BEGIN

const static ImVec2 DEFAULT_IMVEC2 = {0.0f, 0.0f};

class ImGuiObj
{
protected:
    ImVec2 _windowPos;
    ImVec2 _windowSize;
    
protected:
    ImGuiObj(const ImVec2& windowPos_ = DEFAULT_IMVEC2, const ImVec2& windowSize = DEFAULT_IMVEC2);
    
protected:
    void begin(const char* name);
    void end();
    
public:
    virtual void update() = 0;
};

using ImGuiObjPtr = std::shared_ptr<ImGuiObj>;

NS_ACE_END
