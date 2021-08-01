#include "ImGuiObj.h"
#include "ImguiManager.h"
#include "imgui_internal.h"

USING_NS_ACE

ImGuiObj::ImGuiObj()
{
    
}

void ImGuiObj::begin(const char * name)
{
    ImGui::Begin(name);
//    ImGui::SetWindowFontScale(ImguiManager::getInstance()->windowScale_ * 1.5f);
}

void ImGuiObj::end()
{
    ImGui::End();
}

void ImGuiObj::setWindowPos(float w, float h)
{
    float windowScale = ImguiManager::getInstance()->windowScale_;
    windowPos_ = { w * windowScale, h * windowScale };
}

void ImGuiObj::setWindowSize(float w, float h)
{
    float windowScale = ImguiManager::getInstance()->windowScale_;
    windowSize_ = { w * windowScale, h * windowScale };
}

void ImGuiObj::ScrollWhenDraggingOnVoid(const ImVec2 &delta, const char* name)
{
    ImGuiContext& g = *ImGui::GetCurrentContext();
    ImGuiWindow* window = g.CurrentWindow;
    bool hovered = false;
    bool held = false;
    if (g.HoveredId == 0) // If nothing hovered so far in the frame (not same as IsAnyItemHovered()!)
        ImGui::ButtonBehavior(window->Rect(), window->GetID(name), &hovered, &held, ImGuiButtonFlags_MouseButtonLeft);
    
    ImGuiIO& io = ImGui::GetIO();
    if(true == io.MouseDown[0] && true == isFirstScroll)
    {
        isFirstScroll = false;
        return;
    }
    else if(false == io.MouseDown[0] && false == isFirstScroll)
    {
        isFirstScroll = true;
    }
    
    if(true == isFirstScroll)
        return;
    
    if (held && delta.x != 0.0f)
        ImGui::SetScrollX(window, window->Scroll.x + delta.x);
    if (held && delta.y != 0.0f)
        ImGui::SetScrollY(window, window->Scroll.y + delta.y);
}
