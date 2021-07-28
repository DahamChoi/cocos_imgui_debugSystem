#include "ImguiManager.h"

#include "imgui_impl_cocos2dx.h"
#include "ImGuiImeDelegate.h"

#include "DebugLogGui.h"

#include <platform/CCFileUtils.h>

USING_NS_ACE

bool ImguiManager::initSingle()
{
    ImGui_ImplCocos2dx_Init(true);
    
    // 한글 폰트 적용
    ImGuiIO& io = ImGui::GetIO();
    std::string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename("fonts/NotoSansKR-Medium.otf");
    io.Fonts->AddFontFromFileTTF(filePath.c_str(), 32.0f, NULL, io.Fonts->GetGlyphRangesKorean());
    
    // 윈도우 스케일
    const cocos2d::Size& pixelSize = cocos2d::Director::getInstance()->getWinSizeInPixels();
    windowScale_ = pixelSize.width / 1024.f;
    
    return true;
}

void ImguiManager::process()
{
    // create frame
    ImGui_ImplCocos2dx_NewFrame();

    // draw all gui
    update();

    // render
    ImGui::Render();
    ImGui_ImplCocos2dx_RenderDrawData(ImGui::GetDrawData());
    
    // Delegater update
    ImGuiImeDelegate::getInstance()->update();
    
    // Detect Gesture
    detectDebugGesture();
}

void ImguiManager::update()
{
    for(auto& pImGui : mapImGui)
    {
        pImGui.second->update();
    }
    
    for(auto& key : vecLateRemoveMapImGui)
    {
        mapImGui.erase(key);
    }
    vecLateRemoveMapImGui.clear();
}

void ImguiManager::detectDebugGesture()
{
    ImGuiIO& io = ImGui::GetIO();
    
    touchMovedDistance_ += abs(io.MouseDelta.x) + abs(io.MouseDelta.y);
    possibleGestureTime_ += cocos2d::Director::getInstance()->getDeltaTime();
    
    if(touchMovedDistance_ > 1000.f && possibleGestureTime_ > 3.f)
    {
        if(true == isPossibleKey(DebugLogGui::DebugLogGuiKey))
        {
            ImGuiObjPtr pImGui = std::make_shared<DebugLogGui>();
            addImGui(DebugLogGui::DebugLogGuiKey, pImGui);
        }
        
        possibleGestureTime_ = 0.f;
        touchMovedDistance_ = 0.f;
    }
 
    if(false == io.MouseDown[0])
    {
        touchMovedDistance_ = 0.f;
        possibleGestureTime_ = 0.f;
    }
}

bool ImguiManager::addImGui(const std::string& key, const ImGuiObjPtr& pImGui)
{
    if(false == isPossibleKey(key))
        return false;
    
    mapImGui.insert({key, pImGui});
    return true;
}

bool ImguiManager::isPossibleKey(const std::string& key)
{
    auto iter = mapImGui.find(key);
    bool isPossible = iter == mapImGui.end();
    return isPossible;
}

void ImguiManager::removeImGui(const std::string& key)
{
    vecLateRemoveMapImGui.push_back(key);
}

