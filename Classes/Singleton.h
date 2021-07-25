//
//  Singleton.h
//  cocos_mygui_debugSystem
//
//  Created by 최다함 on 2021/07/25.
//

#pragma once

#include "ace.h"

#include <assert.h>

NS_ACE_BEGIN

class SingletonInterface
{
public:
    virtual void Destroy() {};
};

template <typename T>
class Singleton : public SingletonInterface
{
protected:
    static T* pInst;
    Singleton() {};
    
protected:
    virtual bool initSingle() { return true; }
    virtual void beforeDestroy() {};

public:
    virtual void Destroy() { Singleton<T>::destroyInstance(); }
    
public:
    static T* getInstance()
    {
        if(pInst == nullptr)
        {
            pInst = new T;
            if(pInst->initSingle() == false)
            {
                delete pInst;
                pInst = nullptr;
                assert(0);
            }
        }
        
        return pInst;
    }
    
    static void destroyInstance()
    {
        if(pInst == nullptr)
            return;
        
        pInst->beforeDestroy();
        
        delete pInst;
        pInst = nullptr;
    }
};

template <typename T>
T* Singleton<T>::pInst = nullptr;

NS_ACE_END
