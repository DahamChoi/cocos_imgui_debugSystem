#include "AceScene.h"
#include "ImguiManager.h"

#include "AceLog.h"

USING_NS_CC;
USING_NS_ACE

void AceScene::render(cocos2d::Renderer* renderer, const cocos2d::Mat4* eyeTransforms, const cocos2d::Mat4* eyeProjections, unsigned int multiViewCount)
{
    Scene::render(renderer, eyeTransforms, eyeProjections, multiViewCount);
    
    ImguiManager::getInstance()->process();
}
