//
//  BiBiAction.h
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//
//

#ifndef __BiBiGame__BiBiAction__
#define __BiBiGame__BiBiAction__

#include <iostream>
#include "Defines.h"
#include "cocos2d.h"
using namespace cocos2d;

class BiBiAction:public CCSprite
{
public:
    BiBiAction();
    ~BiBiAction();
    
//    //动作方法
//    void HeroAction();
    
    //运行间隔
    void update(float date);
    
    //动作
    CC_SYNTHESIZE_RETAIN(CCAction*, _idleAction, idleAction);
    CC_SYNTHESIZE_RETAIN(CCAction*, _attackAction, attackAction);
    CC_SYNTHESIZE_RETAIN(CCAction*, _walkAction, walkAction);
    CC_SYNTHESIZE_RETAIN(CCAction*, _hurtAction, hurtAction);
    CC_SYNTHESIZE_RETAIN(CCAction*, _knockoutAction, knockoutAction);
    CC_SYNTHESIZE_RETAIN(CCAction*, _skillAction, skillAction);
    
    //保存当前动作
    CC_SYNTHESIZE(ActionState, _actionState, ActionState);
    
    //属性
    CC_SYNTHESIZE(float, _WalkSpeed, WalkSpeed);
    CC_SYNTHESIZE(float, _HpCount, HpCount);
    CC_SYNTHESIZE(float, _damage, Damage);
    
    //记录精灵如何在地图移动
    CC_SYNTHESIZE(cocos2d::CCPoint, _velocity, Velocity);
    CC_SYNTHESIZE(cocos2d::CCPoint, _desiredPosition, DesiredPosition);
    
    //保存对精灵的实际图像有用的测量值。
    CC_SYNTHESIZE(float, _centerToSides, CenterToSides);
    CC_SYNTHESIZE(float, _centerToBottom, CenterToBottom);
    
    //禁止
    void idle();
    void idleSkill();
    
    //行走
    int walkWithDirection(CCPoint direction);
    
    //攻击
    void attack();
    CCArray *FireArr;
    int numFire;
    
    //受伤
    void hurtWithDamage(float damage);
    
    //击倒
    void knockout();
    
    //技能
    void skill();
    
    //几率方向参数
    int a;
    
    //盒子碰撞
    CC_SYNTHESIZE(BoundingBox, _hitBox, Hitbox);
    CC_SYNTHESIZE(BoundingBox, _attackBox,Attackbox);
    BoundingBox createBoundingBoxWithOrigin(cocos2d::CCPoint origin, cocos2d::CCSize size);
    void transformBoxes();
    void setPosition(CCPoint position);
    
    
};

#endif /* defined(__BiBiGame__BiBiAction__) */
