//
//  Boss.h
//  BiBiGame
//
//  Created by Zhusy on 13-7-2.
//
//

#ifndef __BiBiGame__Boss__
#define __BiBiGame__Boss__

#include <iostream>
#include "cocos2d.h"
#include "BiBiAction.h"
using namespace cocos2d;

class Boss:public BiBiAction
{
public:
    CREATE_FUNC(Boss);
    bool init();
    
    CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);
};

#endif /* defined(__BiBiGame__Boss__) */
