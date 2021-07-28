#include "ImGuiImeDelegate.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "AceLog.h"
#include "cocos2d.h"

#include <string>

USING_NS_ACE;
USING_NS_CC;

bool ImGuiImeDelegate::initSingle()
{
    return true;
}

bool ImGuiImeDelegate::attachWithIME()
{
    bool ret = IMEDelegate::attachWithIME();
    if (ret)
    {
        // open keyboard
        auto pGlView = Director::getInstance()->getOpenGLView();
        if (pGlView)
        {
            pGlView->setIMEKeyboardState(true);
        }
    }
    return ret;
}

bool ImGuiImeDelegate::detachWithIME()
{
    bool ret = IMEDelegate::detachWithIME();
    if (ret)
    {
        // close keyboard
        auto glView = Director::getInstance()->getOpenGLView();
        if (glView)
        {
            glView->setIMEKeyboardState(false);
        }
    }
    return ret;
}

bool ImGuiImeDelegate::canAttachWithIME()
{
    return true;
}

bool ImGuiImeDelegate::canDetachWithIME()
{
    return true;
}

void ImGuiImeDelegate::insertText(const char * text, size_t len)
{
    std::string insert(text, len);

    ImGuiIO& io = ImGui::GetIO();
    
    auto pos = insert.find(StringUtils::AsciiCharacters::NewLine);
    if (insert.npos != pos)
    {
        len = pos;
        insert.erase(pos);
        io.KeysDown[(int)cocos2d::EventKeyboard::KeyCode::KEY_ENTER] = true;
    }
    
    if(len > 0)
    {
        io.AddInputCharactersUTF8(text);
        AceLog::log(text);
    }
}

void ImGuiImeDelegate::deleteBackward()
{
    ImGuiIO& io = ImGui::GetIO();
    io.AddInputCharacter(IM_UNICODE_CODEPOINT_MAX);
    io.KeysDown[(int)cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE] = true;
}

void ImGuiImeDelegate::update()
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[(int)cocos2d::EventKeyboard::KeyCode::KEY_ENTER] = false;
    io.KeysDown[(int)cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE] = false;
}
