//
//  tBoss.h
//  BiBiGame
//
//  Created by Zhusy on 13-7-12.
//
//

#ifndef __BiBiGame__tBoss__
#define __BiBiGame__tBoss__

#include <iostream>
#include "cocos2d.h"
#include "BiBiAction.h"
using namespace cocos2d;

class tBoss:public BiBiAction
{
public:
    CREATE_FUNC(tBoss);
    bool init();
    
    CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);
};

#endif /* defined(__BiBiGame__tBoss__) */
