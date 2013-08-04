//
//  tBoss.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-7-12.
//
//

#include "tBoss.h"

bool tBoss::init()
{
    bool bRet = false;
    do
    {
        _nextDecisionTime = 0;
        CC_BREAK_IF(!BiBiAction::initWithSpriteFrameName("tBoss_idle_1.png"));
        //怪物动作
        CCArray *idleFrames = CCArray::createWithCapacity(2);
        for (int i=1; i<3; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("tBoss_idle_%d.png", i)->getCString());
            idleFrames->addObject(frame);
        }
        CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(idleFrames, float(1.0 / 8.0));
        this->setidleAction(CCRepeatForever::create(CCAnimate::create(idleAnimation)));
        
        //attack animation
        CCArray *attackFrames = CCArray::createWithCapacity(2);
        for (int i=1; i<3; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("tBoss_idle_%d.png", i)->getCString());
            attackFrames->addObject(frame);
        }
        CCAnimation *attackAnimation = CCAnimation::createWithSpriteFrames(attackFrames, float(1.0 / 8.0));
        this->setattackAction(CCSequence::create(CCAnimate::create(attackAnimation), CCCallFunc::create(this, callfunc_selector(tBoss::idle)), NULL));
        
        //walk animation
        CCArray *walkFrames = CCArray::createWithCapacity(2);
        for (int i = 1; i < 3; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("tBoss_walk_%d.png",i)->getCString());
            walkFrames->addObject(frame);
        }
        CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(walkFrames, float(1.0 / 12.0));
        this->setwalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));
        
        //hurt animation
        CCArray *hurtFrames = CCArray::createWithCapacity(1);
        for (int i = 1; i < 2; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("tBoss_hurt_1.png")->getCString());
            hurtFrames->addObject(frame);
        }
        CCAnimation *hurtAnimation = CCAnimation::createWithSpriteFrames(hurtFrames, float(1.0 / 8.0));
        this->sethurtAction(CCSequence::create(CCAnimate::create(hurtAnimation), CCCallFunc::create(this, callfunc_selector(tBoss::idle)), NULL));
        
        //knocked out animation
        CCArray *knockedOutFrames = CCArray::createWithCapacity(1);
        for (int i = 1; i < 2; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("tBoss_idle_1.png")->getCString());
            knockedOutFrames->addObject(frame);
        }
        CCAnimation *knockedOutAnimation = CCAnimation::createWithSpriteFrames(knockedOutFrames, float(1.0 / 12.0));
        this->setknockoutAction(CCSequence::create(CCAnimate::create(knockedOutAnimation),CCBlink::create(1.0, 5.0),CCFadeOut::create(1), NULL));
        
        this->setWalkSpeed(20.0);
        this->setCenterToBottom(100.0);
        this->setCenterToSides(100.0);
        this->setHpCount(300.0);
        this->setDamage(50.0);

        
        bRet = true;
    }while (0) ;
    return bRet;
}
