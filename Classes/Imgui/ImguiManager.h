//
//  ImguiManager.h
//  MPBReboot
//
//  Created by 최다함 on 2021/07/22.
//

#pragma once

#include "ace.h"

#include "Singleton.h"
#include "ImGuiObj.h"

#include <vector>

NS_ACE_BEGIN

class ImguiManager final : public Singleton<ImguiManager>
{
    friend class Singleton<ImguiManager>;

private:
    std::vector<ImGuiObjPtr> vecImGui;
    
public:
    virtual bool initSingle() override;
    
public:
    void update();
    void process();
    
public:
    void addImGui(const ImGuiObjPtr& pImGui);
    
public:
    void removeImGui(const ImGuiObjPtr& pImGui);
    
private:
    ImguiManager() = default;
};

NS_ACE_END
