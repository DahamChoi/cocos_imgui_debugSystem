#pragma once

#include "ace.h"

#include "imgui.h"

NS_ACE_BEGIN

const static ImVec2 DEFAULT_IMVEC2 = {0.0f, 0.0f};

class ImGuiObj
{
protected:
    ImVec2 windowPos_;
    ImVec2 windowSize_;
    
protected:
    ImGuiObj();
    
protected:
    void setWindowPos(float w, float h);
    void setWindowSize(float w, float h);
    
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

