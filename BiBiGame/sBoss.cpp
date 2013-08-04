//
//  sBoss.cpp
//  BiBiGame
//
//  Created by 蛋儿宝A+ on 13-7-6.
//
//

#include "sBoss.h"

bool sBoss::init()
{
    bool bRet = false;
    do
    {
        _nextDecisionTime = 0;
        CC_BREAK_IF(!BiBiAction::initWithSpriteFrameName("sBoss_idle_1.png"));
        //怪物动作
        CCArray *idleFrames = CCArray::createWithCapacity(1);
        for (int i=1; i<2; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("sBoss_idle_%d.png", i)->getCString());
            idleFrames->addObject(frame);
        }
        CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(idleFrames, float(1.0 / 8.0));
        this->setidleAction(CCRepeatForever::create(CCAnimate::create(idleAnimation)));
        
        //attack animation
        CCArray *attackFrames = CCArray::createWithCapacity(2);
        for (int i=1; i<3; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("sBoss_attack_%d.png", i)->getCString());
            attackFrames->addObject(frame);
        }
        CCAnimation *attackAnimation = CCAnimation::createWithSpriteFrames(attackFrames, float(1.0 / 8.0));
        this->setattackAction(CCSequence::create(CCAnimate::create(attackAnimation), CCCallFunc::create(this, callfunc_selector(sBoss::idle)), NULL));
        
        //skill animation
        CCArray *skillFrames = CCArray::createWithCapacity(60);
        for (int i=1; i<61; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("sBoss_skill_%d.png", i)->getCString());
            skillFrames->addObject(frame);
        }
        CCAnimation *skillAnimation = CCAnimation::createWithSpriteFrames(skillFrames, float(1.0 / 8.0));
        this->setskillAction(CCSequence::create(CCAnimate::create(skillAnimation), CCCallFunc::create(this, callfunc_selector(sBoss::idleSkill)), NULL));
        
        //walk animation
        CCArray *walkFrames = CCArray::createWithCapacity(1);
        for (int i = 1; i < 2; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("sBoss_idle_1.png")->getCString());
            walkFrames->addObject(frame);
        }
        CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(walkFrames, float(1.0 / 12.0));
        this->setwalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));
        
        //hurt animation
        CCArray *hurtFrames = CCArray::createWithCapacity(1);
        for (int i = 1; i < 2; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("sBoss_idle_1.png")->getCString());
            hurtFrames->addObject(frame);
        }
        CCAnimation *hurtAnimation = CCAnimation::createWithSpriteFrames(hurtFrames, float(1.0 / 12.0));
        this->sethurtAction(CCSequence::create(CCAnimate::create(hurtAnimation), CCCallFunc::create(this, callfunc_selector(sBoss::idle)), NULL));
        
        //knocked out animation
        CCArray *knockedOutFrames = CCArray::createWithCapacity(1);
        for (int i = 1; i < 2; i++)
        {
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("sBoss_idle_1.png")->getCString());
            knockedOutFrames->addObject(frame);
        }
        CCAnimation *knockedOutAnimation = CCAnimation::createWithSpriteFrames(knockedOutFrames, float(1.0 / 12.0));
        this->setknockoutAction(CCSequence::create(CCAnimate::create(knockedOutAnimation),CCBlink::create(1.0, 5.0),CCFadeOut::create(1), NULL));
        
        this->setWalkSpeed(0.0);
        this->setCenterToBottom(40.0);
        this->setCenterToSides(55.0);
//        int whichlevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("Level");
//        if (whichlevel == 1) {
            this->setHpCount(100.0);
            this->setDamage(0.0);
//        }else if(whichlevel == 2){
//            this->setHpCount(1000.0);
//            this->setDamage(12.0);
//        }
        
//        this->setHitbox(this->createBoundingBoxWithOrigin(ccp(0, 0),CCSizeMake(this->getCenterToSides() * 2, this->getCenterToBottom() * 2)));
//        this->setAttackbox(this->createBoundingBoxWithOrigin(ccp(40, -20), CCSizeMake(80, 40)));
        
        bRet = true;
    }while (0) ;
    return bRet;
}