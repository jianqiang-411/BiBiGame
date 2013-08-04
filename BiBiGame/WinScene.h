//
//  WinScene.h
//  BiBiGame
//
//  Created by Zhusy on 13-7-5.
//
//

#ifndef __BiBiGame__WinScene__
#define __BiBiGame__WinScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class WinScene:public CCScene {
public:
    CREATE_FUNC(WinScene);
    
    bool init();
    void GameLevel();
    
    CCSprite *tiSK;
};

#endif /* defined(__BiBiGame__WinScene__) */
