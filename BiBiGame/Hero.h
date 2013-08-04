//
//  Hero.h
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//
//

#ifndef __BiBiGame__Hero__
#define __BiBiGame__Hero__

#include <iostream>
#include "BiBiAction.h"
#include "cocos2d.h"
using namespace cocos2d;

class Hero:public BiBiAction
{
public:
    CREATE_FUNC(Hero);
//    Hero();
    bool init();
    
    
//    ChooseRobet *_chooseRobet;
};

#endif /* defined(__BiBiGame__Hero__) */
