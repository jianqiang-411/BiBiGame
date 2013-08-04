//
//  FireGirl.h
//  BiBiGame
//
//  Created by Zhusy on 13-7-9.
//
//

#ifndef __BiBiGame__FireGirl__
#define __BiBiGame__FireGirl__

#include <iostream>
#include "cocos2d.h"
#include "BiBiAction.h"
using namespace cocos2d;

class FireGirl:public BiBiAction
{
public:
    CREATE_FUNC(FireGirl);
    bool init();
    
    CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);
};


#endif /* defined(__BiBiGame__FireGirl__) */
