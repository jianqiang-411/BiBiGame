//
//  CartoonScene.h
//  BiBiGame
//
//  Created by Zhusy on 13-7-1.
//
//

#ifndef __BiBiGame__CartoonScene__
#define __BiBiGame__CartoonScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class CartoonScene:public CCScene {
public:
    CREATE_FUNC(CartoonScene);
    bool init();
    void changeScence();
    CCMenu* pMenu;
};


#endif /* defined(__BiBiGame__CartoonScene__) */
