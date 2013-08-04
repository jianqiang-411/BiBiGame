//
//  LoseScene.h
//  BiBiGame
//
//  Created by Zhusy on 13-7-5.
//
//

#ifndef __BiBiGame__LoseScene__
#define __BiBiGame__LoseScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class LoseScene:public CCScene {
public:
    CREATE_FUNC(LoseScene);
    
    bool init();
    void youLose();
    
    CCSprite *loseTiSK;
    
};

#endif /* defined(__BiBiGame__LoseScene__) */
