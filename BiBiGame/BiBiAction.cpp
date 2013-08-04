//
//  BiBiAction.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//
//

#include "BiBiAction.h"

BiBiAction::BiBiAction()
{
    _idleAction = NULL;
    _attackAction = NULL;
    _walkAction = NULL;
    _hurtAction = NULL;
    _knockoutAction = NULL;
    _skillAction = NULL;
}

BiBiAction::~BiBiAction()
{
    
}

void BiBiAction::idle()
{
    if (_actionState != kActionStateIdle)
    {
        this->stopAllActions();
        this->runAction(_idleAction);
        _actionState = kActionStateIdle;
        _velocity = CCPointZero;
    }
}

void BiBiAction::idleSkill()
{
    if (_actionState != kActionStateIdle)
    {
        this->stopAllActions();
        this->runAction(_idleAction);
        _actionState = kActionStateSkill;
        _velocity = CCPointZero;
    }
}

void BiBiAction::attack()
{
    if (_actionState == kActionStateIdle || _actionState == kActionStateAttack || _actionState == kActionStateWalk)
    {
        this->stopAllActions();
        this->runAction(_attackAction);
        _actionState = kActionStateAttack;
    }
}

void BiBiAction::skill()
{
    if (_actionState == kActionStateIdle || _actionState == kActionStateAttack || _actionState == kActionStateWalk)
    {
        this->stopAllActions();
        this->runAction(_skillAction);
        _actionState = kActionStateAttack;
    }
}

//行走
int BiBiAction::walkWithDirection(CCPoint direction)
{
    a = 0;
    if (_actionState == kActionStateIdle)
    {
        this->stopAllActions();
        this->runAction(_walkAction);
        _actionState = kActionStateWalk;
    }
    if (_actionState == kActionStateWalk)
    {
        int ifGirl = CCUserDefault::sharedUserDefault()->getIntegerForKey("ifGirl");
        if (ifGirl == 1) {
            _velocity = ccp(direction.x * 20, direction.y *_WalkSpeed);
            CCUserDefault::sharedUserDefault()->setIntegerForKey("ifGirl", 0);
        }else{
            _velocity = ccp(direction.x *_WalkSpeed, direction.y *_WalkSpeed);
        }
        
        if (direction.x >= 0)
        {
            this->setScaleX(1.0);
            a=1;
        }
        else
        {
            this->setScaleX(-1.0);
            a=2;
        }
    }
    return a;
}

void BiBiAction::update(float dt)
{
    if (_actionState == kActionStateWalk)
    {
        _desiredPosition = ccpAdd(this->getPosition(), ccpMult(_velocity, dt));
    }
}

//第一个方法创建一个新的包围盒，这有助于ActionSprite的子类创建属于它们自己的包围盒。第二个方法，基于精灵的位置、比例因子，和包围盒原本的原点和大小来更新每个包围盒实际测量的原点和大小。之所以要用到比例因子，是因为它决定着精灵的方向。位于精灵右侧的盒子，当比例因子设置为-1时，将会翻转到左侧。
BoundingBox BiBiAction::createBoundingBoxWithOrigin(CCPoint origin, CCSize size)
{
    BoundingBox boundingBox;
    boundingBox.original.origin = origin;
    boundingBox.original.size = size;
    boundingBox.actual.origin = ccpAdd(this->getPosition(), ccp(boundingBox.original.origin.x, boundingBox.original.origin.y));
    boundingBox.actual.size = size;
    return boundingBox;
}

void BiBiAction::transformBoxes()
{
    _hitBox.actual.origin = ccpAdd(this->getPosition(), ccp(_hitBox.original.origin.x, _hitBox.original.origin.y));
    _attackBox.actual.origin = ccpAdd(this->getPosition(), ccp(_attackBox.original.origin.x + (this->getScaleX() == -1 ? (- _attackBox.original.size.width - _hitBox.original.size.width) : 0),_attackBox.original.origin.y));
}

void BiBiAction::setPosition(CCPoint position)
{
    CCSprite::setPosition(position);
    this->transformBoxes();
}

//受伤
void BiBiAction::hurtWithDamage(float damage)
{
    int randnum = 0;
    if (_actionState != kActionStateKnockedOut)
    {
        int ifBoss = CCUserDefault::sharedUserDefault()->getIntegerForKey("ifBoss");
        if (ifBoss == 0 || ifBoss == 1 || ifBoss == 2 || ifBoss == 5) {
            this->stopAllActions();
            this->runAction(_hurtAction);
            _actionState = kActionStateHurt;
            _HpCount -= damage;
        }else if (ifBoss == 3 || ifBoss == 12)
        {
            randnum = random_range(0, 2);
            if (randnum == 0) {
                this->stopAllActions();
                this->runAction(_hurtAction);
                _actionState = kActionStateHurt;
                _HpCount -= damage;
            }else{
                _HpCount -= damage;
            }
        }else if (ifBoss == 4)
        {
            randnum = random_range(0, 1);
            if (randnum == 0) {
                this->stopAllActions();
                this->runAction(_hurtAction);
                _actionState = kActionStateHurt;
                _HpCount -= damage;
            }else{
                _HpCount -= damage;
            }
        }
        else if (ifBoss == 10)
        {
            randnum = random_range(0, 3);
            if (randnum == 0) {
                this->stopAllActions();
                this->runAction(_hurtAction);
                _actionState = kActionStateHurt;
                _HpCount -= damage;
            }else{
                _HpCount -= damage;
            }
        }else if(ifBoss == 11)
        {
            _HpCount -=damage;
        }
        
        if (_HpCount <= 0)
        {
            this->knockout();
        }
    }
}

//击倒
void BiBiAction::knockout()
{
    this->stopAllActions();
    this->runAction(_knockoutAction);
    _HpCount = 0;
    _actionState = kActionStateKnockedOut;
}
