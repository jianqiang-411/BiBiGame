//
//  BiBiScene.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//
//

#include "BiBiScene.h"
using namespace cocos2d;

BiBiScene::BiBiScene()
{
    _bibiLayer = NULL;
    _joystick = NULL;
}

BiBiScene::~BiBiScene()
{

}

bool BiBiScene::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCScene::init());
        
        _bibiLayer = BiBiLayer::create();
        this->addChild(_bibiLayer,0);
        _joystick = Joystick::create();
        this->addChild(_joystick,1);
        //虚拟键盘的
        _joystick->getDPad()->setDelegate(_bibiLayer);
        _joystick->getDDPad()->setDelegate(_bibiLayer);
        _bibiLayer->setjoyS(_joystick);
        
        bRet = true;
    } while (0);
    return bRet;
}