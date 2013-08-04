//
//  MeunScence.h
//  BiBiGame
//
//  Created by Zhusy on 13-6-28.
//
//

#ifndef __BiBiGame__MeunScence__
#define __BiBiGame__MeunScence__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class MeunScence:public CCScene {
public:
    CREATE_FUNC(MeunScence);
    bool init();
    void changeScence();
    void play();
    void logo();
    void xxlogo();
    void highScore();
    CCMenu* pMenu;
    CCMenu *SMenu;
    CCMenu *xMenu;
    CCSprite *logoP;
    
//    void delay();
//    void del();
};


#endif /* defined(__BiBiGame__MeunScence__) */
