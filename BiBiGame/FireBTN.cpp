//
//  FireBTN.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-7-9.
//
//

#include "FireBTN.h"
using namespace cocos2d;

FireBTN::FireBTN(void)
{
    _delegate = NULL;
}

FireBTN::~FireBTN(void)
{
}

FireBTN* FireBTN::dPadWithFile(CCString *fileName, float radius)
{
    FireBTN *pRet = new FireBTN();
    if (pRet && pRet->initWithFile(fileName, radius))
    {
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool FireBTN::initWithFile(CCString *filename, float radius)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCSprite::initWithFile(filename->getCString()));
        
        _radius = radius;
        this->scheduleUpdate();
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void FireBTN::onEnterTransitionDidFinish()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

void FireBTN::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool FireBTN::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint location = pTouch->getLocation();
    
    float distanceSQ = ccpDistanceSQ(location, this->getPosition());
    if (distanceSQ <= _radius * _radius)
    {
        _delegate->PressMetoFire(this);

        return true;
    }
    return false;
}


