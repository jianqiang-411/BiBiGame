//
//  Monster.h
//  BiBiGame
//
//  Created by Zhusy on 13-6-25.
//
//

#ifndef __BiBiGame__Monster__
#define __BiBiGame__Monster__

#include <iostream>
#include "cocos2d.h"
#include "BiBiAction.h"
using namespace cocos2d;

class Monster:public BiBiAction
{
public:
    CREATE_FUNC(Monster);
    bool init();
    
    CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);
};

#endif /* defined(__BiBiGame__Monster__) */
