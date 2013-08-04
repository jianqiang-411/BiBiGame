//
//  Hero.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//
//

#include "Hero.h"
#include "ChooseRobet.h"

using namespace cocos2d;


bool Hero::init()
{
    bool bRet = false;
    do
    {
        int num =  CCUserDefault::sharedUserDefault()->getIntegerForKey("num");
        CCArray *idleFrames;
        CCArray *walkFrames;
        CCArray *hurtFrames;
        CCArray *knockedOutFrames;
        if (num == 1) {
          //  if (_chooseRobet->choose == 1) {
    
            
            CC_BREAK_IF(!BiBiAction::initWithSpriteFrameName("player_robet_idle_1.png"));
            //英雄禁止
            idleFrames = CCArray::createWithCapacity(4);
            for (int i=1; i<5; i++) {
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("player_robet_idle_%d.png",i)->getCString());
                idleFrames->addObject(frame);
            }
            
            //英雄走路
            walkFrames = CCArray::createWithCapacity(4);
            for (int i=1; i<5; i++) {
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("player_robet_walk_%d.png",i)->getCString());
                walkFrames->addObject(frame);
            }
            
            //英雄受伤
            hurtFrames = CCArray::createWithCapacity(2);
            for (int i = 1; i < 3; i++)
            {
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("player_robet_hurt_%d.png", i)->getCString());
                hurtFrames->addObject(frame);
            }
            
            //英雄死亡
            knockedOutFrames = CCArray::createWithCapacity(4);
            for (int i = 1; i < 5; i++)
            {
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("player_robet_knockout_%d.png", i)->getCString());
                knockedOutFrames->addObject(frame);
            }
            
            this->setCenterToBottom(35.0);
            this->setCenterToSides(40.0);
            this->setHpCount(100.0);
            this->setDamage(20.0);
            this->setWalkSpeed(200.0);

        }else if(num == 2){
            CC_BREAK_IF(!BiBiAction::initWithSpriteFrameName("player_gold_idle_1.png"));
            //英雄禁止
            idleFrames = CCArray::createWithCapacity(4);
            for (int i=1; i<5; i++) {
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("player_gold_idle_%d.png",i)->getCString());
                idleFrames->addObject(frame);
            }
            
            //英雄走路
            walkFrames = CCArray::createWithCapacity(4);
            for (int i=1; i<5; i++) {
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("player_gold_walk_%d.png",i)->getCString());
                walkFrames->addObject(frame);
            }
            
            //英雄受伤
            hurtFrames = CCArray::createWithCapacity(1);
            for (int i = 1; i < 2; i++)
            {
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("player_gold_hurt_%d.png", i)->getCString());
                hurtFrames->addObject(frame);
            }
            
            //英雄死亡
            knockedOutFrames = CCArray::createWithCapacity(3);
            for (int i = 1; i < 4; i++)
            {
                CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("player_gold_knockout_%d.png", i)->getCString());
                knockedOutFrames->addObject(frame);
            }
            
            this->setCenterToBottom(40.0);
            this->setCenterToSides(35.0);
            this->setHpCount(100.0);
            this->setDamage(30.0);
            this->setWalkSpeed(150.0);
            
        }
// */
        
        CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(idleFrames, 1.0 / 8.0);
        this->setidleAction(CCRepeatForever::create(CCAnimate::create(idleAnimation)));
         
        CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(walkFrames, float(1.0 / 12.0));
        this->setwalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));
        
        CCAnimation *hurtAnimation = CCAnimation::createWithSpriteFrames(hurtFrames, float(1.0 / 12.0));
        this->sethurtAction(CCSequence::create(CCAnimate::create(hurtAnimation), CCCallFunc::create(this, callfunc_selector(Hero::idle)), NULL));
        
        CCAnimation *knockedOutAnimation = CCAnimation::createWithSpriteFrames(knockedOutFrames, float(1.0 / 12.0));
        this->setknockoutAction(CCSequence::create(CCAnimate::create(knockedOutAnimation), CCBlink::create(2.0, 10.0), NULL));

        
        this->setHitbox(this->createBoundingBoxWithOrigin(ccp(0, 0),CCSizeMake(this->getCenterToSides() * 2, this->getCenterToBottom() * 2)));
        this->setAttackbox(this->createBoundingBoxWithOrigin(ccp(this->getCenterToSides(), -10), CCSizeMake(20, 20)));
        
        
        bRet = true;
    } while (0);
    
    return bRet;

}
