//
//  BiBiScene.h
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//
//

#ifndef __BiBiGame__BiBiScene__
#define __BiBiGame__BiBiScene__

#include <iostream>
#include "BiBiLayer.h"
#include "Joystick.h"
#include "cocos2d.h"
using namespace cocos2d;

class BiBiScene:public CCScene
{
public:
//初始操作
    CREATE_FUNC(BiBiScene);
    
    BiBiScene();
    ~BiBiScene();
    
    virtual bool init();
    
    CC_SYNTHESIZE(BiBiLayer*, _bibiLayer, bibiLayer);
    CC_SYNTHESIZE(Joystick*, _joystick, joystick);
    


};

#endif /* defined(__BiBiGame__BiBiScene__) */
