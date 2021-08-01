#pragma once

#include "ace.h"

#include "Singleton.h"

#include "ImGuiObj.h"

#include <unordered_map>
#include <cocos/cocos2d.h>

NS_ACE_BEGIN

class ImguiManager final : public Singleton<ImguiManager>
{
    friend class Singleton<ImguiManager>;

private:
    std::map<std::string, ImGuiObjPtr> mapImGui;
    std::vector<std::string> vecLateRemoveMapImGui;
    
public:
    float windowScale_ = 1.f;
    
private:
    float lastMoveDistance_ = 0.f;
    float touchMovedDistance_ = 0.f;
    float possibleGestureTime_ = 0.f;
    
public:
    virtual bool initSingle() override;
    
public:
    void update();
    void process();
    void detectDebugGesture();
    
public:
    bool addImGui(const std::string& key, const ImGuiObjPtr& pImGui);
    bool isPossibleKey(const std::string& key);
    
public:
    void removeImGui(const std::string& key);
    
private:
    ImguiManager() = default;
};

NS_ACE_END
