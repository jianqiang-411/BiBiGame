//
//  SLM_SMALL.cpp
//  BiBiGame
//
//  Created by 蛋儿宝A+ on 13-7-11.
//
//

#include "SLM_SMALL.h"

bool SLM_SMALL::init()
{
    bool bRet = false;
    do {
        _nextDecisionTime = 0;
        CC_BREAK_IF(!BiBiAction::initWithSpriteFrameName("ShiLM_3_idle_1.png"));
        //怪物动作
        CCArray *idleFrames = CCArray::createWithCapacity(2);
        for (int i=1; i<3; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("ShiLM_3_idle_%d.png", i)->getCString());
            idleFrames->addObject(frame);
        }
        CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(idleFrames, float(1.0 / 8.0));
        this->setidleAction(CCRepeatForever::create(CCAnimate::create(idleAnimation)));
        
        //attack animation
        CCArray *attackFrames = CCArray::createWithCapacity(1);
        for (int i=1; i<2; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("ShiLM_3_attack_1.png", i)->getCString());
            attackFrames->addObject(frame);
        }
        CCAnimation *attackAnimation = CCAnimation::createWithSpriteFrames(attackFrames, float(1.0 / 24.0));
        this->setattackAction(CCSequence::create(CCAnimate::create(attackAnimation), CCCallFunc::create(this, callfunc_selector(SLM_SMALL::idle)), NULL));
        
        //walk animation
        CCArray *walkFrames = CCArray::createWithCapacity(2);
        for (int i = 1; i < 3; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("ShiLM_3_idle_%d.png", i)->getCString());
            walkFrames->addObject(frame);
        }
        CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(walkFrames, float(1.0 / 12.0));
        this->setwalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));
        
        //hurt animation
        CCArray *hurtFrames = CCArray::createWithCapacity(1);
        for (int i = 1; i < 2; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("ShiLM_3_hurt_1.png", i)->getCString());
            hurtFrames->addObject(frame);
        }
        CCAnimation *hurtAnimation = CCAnimation::createWithSpriteFrames(hurtFrames, float(1.0 / 12.0));
        this->sethurtAction(CCSequence::create(CCAnimate::create(hurtAnimation), CCCallFunc::create(this, callfunc_selector(SLM_SMALL::idle)), NULL));
        
        //knocked out animation
        CCArray *knockedOutFrames = CCArray::createWithCapacity(2);
        for (int i = 1; i < 3; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("ShiLM_3_idle_%d.png", i)->getCString());
            knockedOutFrames->addObject(frame);
        }
        CCAnimation *knockedOutAnimation = CCAnimation::createWithSpriteFrames(knockedOutFrames, float(1.0 / 12.0));
        this->setknockoutAction(CCSequence::create(CCAnimate::create(knockedOutAnimation),CCRotateTo::create(0.2, 180),CCBlink::create(1.0, 5.0),CCFadeOut::create(0.5), NULL));
        
        this->setWalkSpeed(150.0);
        this->setCenterToBottom(23.0);
        this->setCenterToSides(23.0);
        this->setHpCount(30.0);
        this->setDamage(2.0);
        
        
        //        this->setHitbox(this->createBoundingBoxWithOrigin(ccp(-5, -this->getCenterToBottom()),CCSizeMake(this->getCenterToSides() * 2-30, this->getCenterToBottom() * 2)));
        //        this->setAttackbox(this->createBoundingBoxWithOrigin(ccp(5, 0), CCSizeMake(35, 28)));
        
        
        bRet = true;
    } while (0);
    return bRet;
}