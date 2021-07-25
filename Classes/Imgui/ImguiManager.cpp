#include "ImguiManager.h"

#include "imgui_impl_cocos2dx.h"
#include "ImGuiImeDelegate.h"

#include <platform/CCFileUtils.h>

USING_NS_ACE;

bool ImguiManager::initSingle()
{
    ImGui_ImplCocos2dx_Init(true);
    
    // 한글 폰트 적용
    ImGuiIO& io = ImGui::GetIO();
    std::string filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename("fonts/NotoSansKR-Medium.otf");
    io.Fonts->AddFontFromFileTTF(filePath.c_str(), 16.0f, NULL, io.Fonts->GetGlyphRangesKorean());
    
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
}

void ImguiManager::update()
{
    for(auto& pImGui : vecImGui)
    {
        pImGui->update();
    }
}

void ImguiManager::addImGui(const ImGuiObjPtr& pImGui)
{
    vecImGui.push_back(pImGui);
}

void ImguiManager::removeImGui(const ImGuiObjPtr& pImGui)
{
    auto iter = std::find(vecImGui.begin(), vecImGui.end(), pImGui);
    if(iter != vecImGui.end())
    {
        vecImGui.erase(iter);
    }
}

