//
//  FireBTN.h
//  BiBiGame
//
//  Created by Zhusy on 13-7-9.
//
//

#ifndef __BiBiGame__FireBTN__
#define __BiBiGame__FireBTN__

#include <iostream>
#pragma once
#include"cocos2d.h"

class FireBTN;

class FireBTNDelegate
{
public:
    virtual void PressMetoFire(FireBTN *simpleDPad) = 0;

};

class FireBTN : public cocos2d::CCSprite, public cocos2d::CCTargetedTouchDelegate
{
public:
    FireBTN(void);
    ~FireBTN(void);
    
    static FireBTN* dPadWithFile(cocos2d::CCString *fileName, float radius);
    bool initWithFile(cocos2d::CCString *filename, float radius);
    
    void onEnterTransitionDidFinish();
    void onExit();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    CC_SYNTHESIZE(FireBTNDelegate*, _delegate, Delegate);
    
protected:
    float _radius;
};

#endif /* defined(__BiBiGame__FireBTN__) */
