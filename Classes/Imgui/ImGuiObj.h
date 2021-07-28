#pragma once

#include "ace.h"

#include "imgui.h"

NS_ACE_BEGIN

const static ImVec2 DEFAULT_IMVEC2 = {0.0f, 0.0f};

class ImGuiObj
{
protected:
    ImVec2 _windowPos;
    ImVec2 _windowSize;
    
protected:
    ImGuiObj(const ImVec2& windowPos_ = DEFAULT_IMVEC2, const ImVec2& windowSize_ = DEFAULT_IMVEC2);
    
protected:
    void begin(const char* name);
    void end();
    
protected:
    void ScrollWhenDraggingOnVoid(const ImVec2 &delta, const char* name);
    
private:
    bool isFirstScroll = true;
    
public:
    virtual void update() = 0;
};

using ImGuiObjPtr = std::shared_ptr<ImGuiObj>;

NS_ACE_END

