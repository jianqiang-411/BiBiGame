//
//  sBoss.h
//  BiBiGame
//
//  Created by 蛋儿宝A+ on 13-7-6.
//
//

#ifndef __BiBiGame__sBoss__
#define __BiBiGame__sBoss__

#include <iostream>
#include "cocos2d.h"
#include "BiBiAction.h"
using namespace cocos2d;

class sBoss:public BiBiAction
{
public:
    CREATE_FUNC(sBoss);
    bool init();
    
    CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);
};

#endif /* defined(__BiBiGame__sBoss__) */
