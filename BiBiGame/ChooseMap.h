//
//  ChooseMap.h
//  BiBiGame
//
//  Created by Zhusy on 13-7-11.
//
//

#ifndef __BiBiGame__ChooseMap__
#define __BiBiGame__ChooseMap__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class ChooseMap:public CCScene {
    
public:
    CREATE_FUNC(ChooseMap);
    
    bool init();
    
    void choose_1_Map();
    void choose_2_Map();
    void choose_3_Map();
};

#endif /* defined(__BiBiGame__ChooseMap__) */
