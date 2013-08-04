//
//  Joystick.h
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//
//

#ifndef __BiBiGame__Joystick__
#define __BiBiGame__Joystick__

#include <iostream>
#include "cocos2d.h"
#include "SimpleDPad.h"
#include "FireBTN.h"
#include "Hero.h"
using namespace cocos2d;

class Joystick:public CCLayer
{
public:
    CREATE_FUNC(Joystick);
    Joystick();
    //虚拟键盘
    bool init();
    CC_SYNTHESIZE(SimpleDPad*, _dPad, DPad);
    CC_SYNTHESIZE(FireBTN*, _ddPad, DDPad);
    
    //血条
    Hero *_hero;
    CCArray *_bloodArr;
    CCSprite *_sBlood;
    
    void createTitleSprites(int _iHpCount);
    void deleteTitleSprites(int _iDamage);
    
    void stop();
    void restart();
    void menu();
    void back();
    
    CCSprite *stopBackground;
    CCMenu *pmenu;
    CCMenu *sMenu;
    
    int iNum = 99;
    
    void endGame();
    void winGame();
    
    void initSnow();
    
    void timeLabel();
    CCLabelTTF *timeLb;
    int nowTime = 1;
    
};

#endif /* defined(__BiBiGame__Joystick__) */
