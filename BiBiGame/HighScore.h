//
//  HighScore.h
//  BiBiGame
//
//  Created by Zhusy on 13-7-10.
//
//

#ifndef __BiBiGame__HighScore__
#define __BiBiGame__HighScore__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class HighScore:public CCScene {
public:
    CREATE_FUNC(HighScore);
    bool init();
    void back();
    
    void initHighScore_1();
    void initHighScore_2();
    void initHighScore_3();
};

#endif /* defined(__BiBiGame__HighScore__) */
