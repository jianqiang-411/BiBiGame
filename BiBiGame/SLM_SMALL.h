//
//  SLM_SMALL.h
//  BiBiGame
//
//  Created by 蛋儿宝A+ on 13-7-11.
//
//

#ifndef __BiBiGame__SLM_SMALL__
#define __BiBiGame__SLM_SMALL__

#include <iostream>
#include "cocos2d.h"
#include "BiBiAction.h"
using namespace cocos2d;

class SLM_SMALL : public BiBiAction{
    
public:
    CREATE_FUNC(SLM_SMALL);
    bool init();
    CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);
};

#endif /* defined(__BiBiGame__SLM_SMALL__) */
