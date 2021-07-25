//
//  AceScene.h
//  cocos_mygui_debugSystem
//
//  Created by 최다함 on 2021/07/25.
//

#pragma once

#include "ace.h"
#include "cocos2d.h"

NS_ACE_BEGIN

class AceScene : public cocos2d::Scene
{
public:
    virtual void render(cocos2d::Renderer* renderer, const cocos2d::Mat4* eyeTransforms, const cocos2d::Mat4* eyeProjections, unsigned int multiViewCount) override;
};

NS_ACE_END
