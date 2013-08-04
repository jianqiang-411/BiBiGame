//
//  SLM_MIDDLE.h
//  BiBiGame
//
//  Created by 蛋儿宝A+ on 13-7-11.
//
//

#ifndef __BiBiGame__SLM_MIDDLE__
#define __BiBiGame__SLM_MIDDLE__

#include <iostream>
#include "cocos2d.h"
#include "BiBiAction.h"
using namespace cocos2d;

class SLM_MIDDLE : public BiBiAction {
    
public:
    CREATE_FUNC(SLM_MIDDLE);
    bool init();
    CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);
    
};

#endif /* defined(__BiBiGame__SLM_MIDDLE__) */
