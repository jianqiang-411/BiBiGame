//
//  ChooseRobet.h
//  BiBiGame
//
//  Created by 蛋儿宝A+ on 13-6-30.
//
//

#ifndef __BiBiGame__ChooseRobet__
#define __BiBiGame__ChooseRobet__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class ChooseRobet:public CCScene {
public:
    CREATE_FUNC(ChooseRobet);
    bool init();
    void choose_1();
    void choose_2();
    
//    CC_SYNTHESIZE(int, _choose, Choose);
//    int chooseNum();
};

#endif /* defined(__BiBiGame__ChooseRobet__) */
