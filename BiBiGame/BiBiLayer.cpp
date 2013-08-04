//
//  BiBiLayer.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//
//

#include "BiBiLayer.h"
#include "Monster.h"
#include "FireGirl.h"
#include "SLM_BIG.h"
#include "SLM_MIDDLE.h"
#include "SLM_SMALL.h"
#include "Boss.h"
#include "sBoss.h"
#include "tBoss.h"
#include "BiBiScene.h"
#include "MeunScence.h"
#include "WinScene.h"
#include "LoseScene.h"
#define ADDY 64

#pragma mark - 构造函数
BiBiLayer::BiBiLayer()
{
    _tileMap = NULL;
    _hero = NULL;
    _monsters = NULL;
    FireArr = NULL;
    BossFireArr = NULL;
    _boss = NULL;
    _sBossArr = NULL;
    _outMonsterArr = NULL;
    _fireGirlArr = NULL;
    fireGirlFireArr = NULL;
    _SLM_1_Arr = NULL;
    _SLM_2_Arr = NULL;
    _SLM_3_Arr = NULL;
    _tBossArr = NULL;

}

#pragma mark - 析构函数
BiBiLayer::~BiBiLayer()
{
    this->unscheduleUpdate();
    
    if (_monsters)
    {
        _monsters->release();
        _monsters = NULL;
    }
    if (_boss) {
        _boss->release();
        _boss = NULL;
    }
    if (_sBossArr) {
        _sBossArr->release();
        _sBossArr = NULL;
    }
    if (_outMonsterArr) {
        _outMonsterArr->release();
        _outMonsterArr=NULL;
    }
    if (FireArr)
    {
        FireArr->release();
        FireArr = NULL;
    }
    if (BossFireArr) {
        BossFireArr->release();
        BossFireArr = NULL;
    }
    if (fireGirlFireArr) {
        fireGirlFireArr->release();
        fireGirlFireArr = NULL;
    }
    if (_fireGirlArr) {
        _fireGirlArr->release();
        _fireGirlArr = NULL;
    }
    if (_SLM_1_Arr) {
        _SLM_1_Arr->release();
        _SLM_1_Arr = NULL;
    }
    if (_SLM_2_Arr) {
        _SLM_2_Arr->release();
        _SLM_2_Arr = NULL;
    }
    if (_SLM_3_Arr) {
        _SLM_3_Arr->release();
        _SLM_3_Arr = NULL;
    }
    if (_tBossArr) {
        _tBossArr->release();
        _tBossArr = NULL;
    }
}

#pragma mark - 数据初始化
bool BiBiLayer::init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        this->initTileMap();
    
        //添加图片plist文件与ccz文件
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("BiBiGame.plist");
        _actors = CCSpriteBatchNode::create("BiBiGame.pvr.ccz");
        _actors->getTexture()->setAliasTexParameters();
        this->addChild(_actors, -5);
        
        cache = CCSpriteFrameCache::sharedSpriteFrameCache();
        
//        _monster = Monster::create();
        //触碰
        //子弹打中怪物消失，怪物被子弹打中消失
        this->_monsters = CCArray::create();
        this->_monsters->retain();
        this->_fireGirlArr = CCArray::create();
        this->_fireGirlArr->retain();
        this->_boss = CCArray::create();
        this->_boss->retain();
        this->_sBossArr = CCArray::create();
        this->_sBossArr->retain();
        this->_outMonsterArr = CCArray::create();
        this->_outMonsterArr->retain();
        this->FireArr = CCArray::create();
        this->FireArr->retain();
        this->BossFireArr = CCArray::create();
        this->BossFireArr->retain();
        this->fireGirlFireArr = CCArray::create();
        this->fireGirlFireArr->retain();
        this->_SLM_1_Arr = CCArray::create();
        this->_SLM_1_Arr->retain();
        this->_SLM_2_Arr = CCArray::create();
        this->_SLM_2_Arr->retain();
        this->_SLM_3_Arr = CCArray::create();
        this->_SLM_3_Arr->retain();
        this->_tBossArr = CCArray::create();
        this->_tBossArr->retain();
        //↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
        
        this->initHero();
//        this->setTouchEnabled(true);
        this->initProjectile();
        this->scheduleUpdate();
        this->initMonsters();
        this->initBosses();
        this->initFireGirl();
        
        int whichlevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("Level");
        if (whichlevel == 3) {
            this->initBigSLM();
            this->initMiddleSLM();
            this->initSmallSLM();
        }else if(whichlevel == 2){
            this->setoutMonsterArr(CCArray::createWithCapacity(105));
            this->setSLM_2_Arr(CCArray::createWithCapacity(105));
        }
        
        
        bRet = true;
    } while (0);
    return bRet;
}

void BiBiLayer::initHero()
{
    _hero = Hero::create();
    _actors->addChild(_hero);
    _hero->setPosition(ccp(_hero->getCenterToSides(), 80+ADDY));
    _hero->setDesiredPosition(_hero->getPosition());
    _hero->idle();
}

void BiBiLayer::initProjectile()
{
    numFire = 0;
    numBossFire = 0;
    numFireGirlFire = 0;
    CCSprite *projectile;
    CCSprite *bossProjectile;
    CCSprite *fireGirlProjectile;
    int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("num");
    
    for (int i=0; i<50; i++) {
        if (num == 1) {
            projectile = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("fire_1.png"));
        }else if(num == 2){
            projectile = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("fire_2.png"));
        }
        
        projectile->setPosition(ccp(460, 300));
        projectile->setVisible(false);
        _actors->addChild(projectile);
        FireArr->addObject(projectile);

    }
    
    for (int i=0; i<50; i++) {
        bossProjectile = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("fire_3.png"));
        
        bossProjectile->setPosition(ccp(460, 300));
        bossProjectile->setVisible(false);
        _actors->addChild(bossProjectile);
        BossFireArr->addObject(bossProjectile);
    }
    
    for (int i=0; i<100; i++) {
        fireGirlProjectile = CCSprite::createWithSpriteFrame(cache->spriteFrameByName("fire_4.png"));
        
        fireGirlProjectile->setPosition(ccp(460, 300));
        fireGirlProjectile->setVisible(false);
        _actors->addChild(fireGirlProjectile);
        fireGirlFireArr->addObject(fireGirlProjectile);
    }
}

//怪物添加
void BiBiLayer::initMonsters()
{
    int monsterCount = 0;
    int whichlevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("Level");
    if (whichlevel == 1) {
        monsterCount = 10;
    }else if(whichlevel == 2){
        monsterCount = 20;
    }
    this->setmonsters(CCArray::createWithCapacity(monsterCount));
    
    for (int i = 0; i < monsterCount; i++)
    {
        Monster *monster = Monster::create();
        _actors->addChild(monster);
        
        //碰撞
//        monster->setTag(1);
//        _arrMonster->addObject(monster);
        //↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
        
        _monsters->addObject(monster);
        
        int minX = SCREEN.width + monster->getCenterToSides();
        int maxX = _tileMap->getMapSize().width * _tileMap->getTileSize().width - monster->getCenterToSides();
        int minY = monster->getCenterToBottom()+ADDY;
        int maxY = 3 * _tileMap->getTileSize().height + monster->getCenterToBottom()+ADDY;
        monster->setScaleX(-1);
        monster->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
        monster->setDesiredPosition(monster->getPosition());
        monster->idle();
    }
}

void BiBiLayer::initBosses()
{
    int whichlevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("Level");
    if (whichlevel == 1) {
        int bossCount = 1;
        this->setboss(CCArray::createWithCapacity(bossCount));
        for (int i=0; i<bossCount; i++) {
            Boss *boss = Boss::create();
            _actors->addChild(boss);
            _boss->addObject(boss);
            
            boss->setScaleX(-1);
            int x = _tileMap->getMapSize().width*_tileMap->getTileSize().width;
            CCLog("-----%d",x);
            boss->setPosition(ccp(x - boss->getCenterToSides(), 100+ADDY));
//            boss->setPosition(ccp(300, 100));
            boss->setDesiredPosition(boss->getPosition());
            boss->idle();
        }
    }
    if(whichlevel == 2){
        int sBossCount = 1;
        this->setsBossArr(CCArray::createWithCapacity(sBossCount));
        for (int i=0; i<sBossCount; i++) {
            sBoss *sboss = sBoss::create();
            _actors->addChild(sboss);
            _sBossArr->addObject(sboss);
            
            sboss->setScaleX(1);
            int x = _tileMap->getMapSize().width*_tileMap->getTileSize().width;
            sboss->setPosition(ccp(x - sboss->getCenterToSides()-80, 90+ADDY));
//            sboss->setPosition(ccp(300, 70));
            sboss->setDesiredPosition(sboss->getPosition());
            sboss->idle();
        }
    }
    if (whichlevel == 3) {
        int tBossCount = 1;
        this->setboss(CCArray::createWithCapacity(tBossCount));
        for (int i=0; i<tBossCount; i++) {
            tBoss *tBBoss = tBoss::create();
            _actors->addChild(tBBoss);
            _tBossArr->addObject(tBBoss);
            
            tBBoss->setScaleX(-1);
            int x = _tileMap->getMapSize().width*_tileMap->getTileSize().width;
            CCLog("-----%d",x);
            tBBoss->setPosition(ccp(x - tBBoss->getCenterToSides(), 140+ADDY));
//            tBBoss->setPosition(ccp(400, 140+ADDY));
            tBBoss->setDesiredPosition(tBBoss->getPosition());
            tBBoss->idle();
        }
    }
}

void BiBiLayer::initFireGirl()
{
    int fireGirlCount = 0;
    int whichlevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("Level");
    if (whichlevel == 1 || whichlevel == 3) {
        fireGirlCount = 6;
    }else if(whichlevel == 2){
        fireGirlCount = 11;
    }
    this->setfireGirlArr(CCArray::createWithCapacity(fireGirlCount));
    
    if (whichlevel == 1 || whichlevel == 3) {
        for (int i = 0; i < fireGirlCount-2; i++)
        {
            FireGirl *girls = FireGirl::create();
            _actors->addChild(girls);
            
            _fireGirlArr->addObject(girls);
            
            int minY = girls->getCenterToBottom()+ADDY;
            int maxY = 3 * _tileMap->getTileSize().height + girls->getCenterToBottom()+ADDY;
            girls->setScaleX(-1);
            girls->setPosition(ccp(1000 + 300 * i, random_range(minY, maxY)));
            girls->setDesiredPosition(girls->getPosition());
            girls->idle();
        }

    }else if(whichlevel == 2 ){
        for (int i = 0; i < 2; i++)
        {
            FireGirl *girls = FireGirl::create();
            _actors->addChild(girls);
            
            _fireGirlArr->addObject(girls);
            
            int minY = girls->getCenterToBottom()+ADDY;
            int maxY = 3 * _tileMap->getTileSize().height + girls->getCenterToBottom()+ADDY;
            girls->setScaleX(-1);
            girls->setPosition(ccp(500 + 200 * i, random_range(minY, maxY)));
            girls->setDesiredPosition(girls->getPosition());
            girls->idle();
        }
        for (int i = 0; i < 2; i++)
        {
            FireGirl *girls = FireGirl::create();
            _actors->addChild(girls);
            
            _fireGirlArr->addObject(girls);
            
            int minY = girls->getCenterToBottom()+ADDY;
            int maxY = 3 * _tileMap->getTileSize().height + girls->getCenterToBottom()+ADDY;
            girls->setScaleX(-1);
            girls->setPosition(ccp(1400, random_range(minY, maxY)));
            girls->setDesiredPosition(girls->getPosition());
            girls->idle();
        }
        for (int i = 0; i < 2; i++)
        {
            FireGirl *girls = FireGirl::create();
            _actors->addChild(girls);
            
            _fireGirlArr->addObject(girls);
            
            int minY = girls->getCenterToBottom()+ADDY;
            int maxY = 3 * _tileMap->getTileSize().height + girls->getCenterToBottom()+ADDY;
            girls->setScaleX(-1);
            girls->setPosition(ccp(1800, random_range(minY, maxY)));
            girls->setDesiredPosition(girls->getPosition());
            girls->idle();
        }
        for (int i = 0; i < 3; i++)
        {
            FireGirl *girls = FireGirl::create();
            _actors->addChild(girls);
            
            _fireGirlArr->addObject(girls);
            
            int minY = girls->getCenterToBottom()+ADDY;
            int maxY = 3 * _tileMap->getTileSize().height + girls->getCenterToBottom()+ADDY;
            girls->setScaleX(-1);
            girls->setPosition(ccp(2300, random_range(minY, maxY)));
            girls->setDesiredPosition(girls->getPosition());
            girls->idle();
        }

    }
    
    
        for (int i=0; i<2; i++) {
        FireGirl *girls = FireGirl::create();
        _actors->addChild(girls);
        
        _fireGirlArr->addObject(girls);
        
        int x = _tileMap->getMapSize().width*_tileMap->getTileSize().width;
        girls->setScaleX(-1);
        girls->setPosition(ccp(x - girls->getCenterToSides()-100, 50+ADDY+i*100));
        girls->setDesiredPosition(girls->getPosition());
        girls->idle();
    }
}

void BiBiLayer::initBigSLM()
{
    int bigSLMCount = 50;
    this->setSLM_1_Arr(CCArray::createWithCapacity(bigSLMCount));
    
    SLM_BIG *bigSLM_1 = SLM_BIG::create();
    _actors->addChild(bigSLM_1);
    _SLM_1_Arr->addObject(bigSLM_1);
    bigSLM_1->setScaleX(-1);
    bigSLM_1->setPosition(ccp(300, 80+ADDY));
    bigSLM_1->setDesiredPosition(bigSLM_1->getPosition());
    bigSLM_1->idle();
    
    SLM_BIG *bigSLM_2 = SLM_BIG::create();
    _actors->addChild(bigSLM_2);
    _SLM_1_Arr->addObject(bigSLM_2);
    bigSLM_2->setScaleX(-1);
    bigSLM_2->setPosition(ccp(1200, 80+ADDY));
    bigSLM_2->setDesiredPosition(bigSLM_2->getPosition());
    bigSLM_2->idle();
    
    for (int i = 0; i < 2; i++) {
        SLM_BIG *bigSLM = SLM_BIG::create();
        _actors->addChild(bigSLM);
        _SLM_1_Arr->addObject(bigSLM);
        bigSLM->setScaleX(-1);
        bigSLM->setPosition(ccp(2500, 100+60*i));
        bigSLM->setDesiredPosition(bigSLM->getPosition());
        bigSLM->idle();
    }
    
    
    
}

void BiBiLayer::initMiddleSLM()
{
    int middleSLMCount = 150;
    this->setSLM_2_Arr(CCArray::createWithCapacity(middleSLMCount));
    for (int i = 0; i < 5; i++) {
        SLM_MIDDLE *middleSLM = SLM_MIDDLE::create();
        _actors->addChild(middleSLM);
        _SLM_2_Arr->addObject(middleSLM);
        
        int minX = SCREEN.width + middleSLM->getCenterToSides()+200;
        int maxX = _tileMap->getMapSize().width * _tileMap->getTileSize().width - middleSLM->getCenterToSides()-400;
        int minY = middleSLM->getCenterToBottom()+ADDY;
        int maxY = 3 * _tileMap->getTileSize().height + middleSLM->getCenterToBottom()+ADDY;
        middleSLM->setScaleX(-1);
        middleSLM->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
        middleSLM->setDesiredPosition(middleSLM->getPosition());
        middleSLM->idle();
    }
}

void BiBiLayer::initSmallSLM()
{
    int smallSLMCount = 400;
    this->setSLM_3_Arr(CCArray::createWithCapacity(smallSLMCount));
    for (int i = 0; i < 6; i++) {
        SLM_SMALL *smallSLM = SLM_SMALL::create();
        _actors->addChild(smallSLM);
        _SLM_3_Arr->addObject(smallSLM);
        
        int minX = SCREEN.width + smallSLM->getCenterToSides()+200;
        int maxX = _tileMap->getMapSize().width * _tileMap->getTileSize().width - smallSLM->getCenterToSides()-400;
        int minY = smallSLM->getCenterToBottom()+ADDY;
        int maxY = 3 * _tileMap->getTileSize().height + smallSLM->getCenterToBottom()+ADDY;
        smallSLM->setScaleX(-1);
        smallSLM->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
        smallSLM->setDesiredPosition(smallSLM->getPosition());
        smallSLM->idle();
    }
}

void BiBiLayer::initTileMap()
{
    int whichlevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("Level");
    if (whichlevel == 1) {
        _tileMap = CCTMXTiledMap::create("pd_tilemap.tmx");
    }else if (whichlevel == 2){
        _tileMap = CCTMXTiledMap::create("pd_tilemap_2.tmx");
    }else if (whichlevel == 3){
        _tileMap = CCTMXTiledMap::create("pd_tilemap_3.tmx");
    }
    
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_tileMap->getChildren(), pObject)
    {
        CCTMXLayer *child = (CCTMXLayer *)pObject;
        child->getTexture()->setAliasTexParameters();
    }
    this->addChild(_tileMap,-10);
}

#pragma mark - 触摸事件
void BiBiLayer::didChangeDirectionTo(SimpleDPad *simpleDPad, cocos2d::CCPoint direction)
{
    _hero->walkWithDirection(direction);
}

void BiBiLayer::isHoldingDirection(SimpleDPad *simpleDPad, cocos2d::CCPoint direction)
{
    _hero->walkWithDirection(direction);
}

void BiBiLayer::simpleDPadTouchEnded(SimpleDPad *simpleDPad)
{
    if (_hero->getActionState()==kActionStateWalk) {
        _hero->idle();
    }
}

void BiBiLayer::PressMetoFire(FireBTN *simpleDPad)
{
    if (_hero->getActionState() != kActionStateKnockedOut) {
        CCSprite *projectile = (CCSprite *)FireArr->objectAtIndex(numFire);
        int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("num");
        if (_hero->a == 2) {
            if (num == 1) {
                projectile->setPosition(ccp(_hero->getPosition().x-20, _hero->getPosition().y-24));
            }else if(num == 2){
                projectile->setPosition(ccp(_hero->getPosition().x-20, _hero->getPosition().y-20));
            }
            //            projectile->setScale(-1);
        }else{
            if (num == 1) {
                projectile->setPosition(ccp(_hero->getPosition().x+20, _hero->getPosition().y-24));
            }else if(num == 2){
                projectile->setPosition(ccp(_hero->getPosition().x+20, _hero->getPosition().y-20));
            }
            
            //            projectile->setScale(1);
        }
        numFire++;
        projectile->setVisible(true);
        if (numFire >= FireArr->count()) {
            numFire = 0;
        }
        
        CCFadeIn *fadein = CCFadeIn::create(0);
        CCMoveBy *move1 = CCMoveBy::create(1, ccp(200, 0));
        CCMoveBy *fmove1 = CCMoveBy::create(1, ccp(-200, 0));
        CCMoveBy *move2 = CCMoveBy::create(1, ccp(120, 0));
        CCMoveBy *fmove2 = CCMoveBy::create(1, ccp(-120, 0));
        CCFadeOut *fade = CCFadeOut::create(0);
        CCMoveTo *moveback = CCMoveTo::create(0, ccp(460, 300));
        CCFiniteTimeAction *FireAction;
        
        if (_hero->a == 2) {
            if (num == 1) {
                FireAction = CCSequence::create(fadein,fmove1,fade,moveback,NULL);
            }else if(num == 2){
                FireAction = CCSequence::create(fadein,fmove2,fade,moveback,NULL);
            }
            
        }else{
            if (num == 1) {
                FireAction = CCSequence::create(fadein,move1,fade,moveback,NULL);
            }else if(num == 2){
                FireAction = CCSequence::create(fadein,move2,fade,moveback,NULL);
            }
        }
        projectile->runAction(FireAction);
    }

}

#pragma mark -  update
void BiBiLayer::update(float dt)
{
    _hero->update(dt);
    this->updatePositions();
    this->setViewpointCenter(_hero->getPosition());
    this->reorderActors();
    this->updateMonsters(dt);
    this->updateOutMonsters(dt);
    this->updateFireGirl(dt);
    this->updateBigSLM(dt);
    this->updateMiddleSLM(dt);
    this->updateSmallSLM(dt);
    this->updateBoss(dt);
    this->updateSBoss(dt);
    this->updateTBoss(dt);
    this->updateHeroProjectile(dt);
    this->updateBossProjectile(dt);
    this->updateFireGirlProjectile(dt);
    this->win_OR_lose();
}

void BiBiLayer::win_OR_lose()
{
    //win
    if (tempBoss == 0 && tempSBoss == 0 && tempTBoss == 0)
    {
        ifWin++;
        if (ifWin == 1) {
            _joyS->winGame();
        }
    }
    
    //lose
    if (_hero->getActionState() == kActionStateKnockedOut)
    {
        ifLose++;
        if (ifLose == 1) {
            _joyS->endGame();

        }
    }
}

void BiBiLayer::updatePositions()
{
    float posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - _hero->getCenterToSides(),MAX(_hero->getCenterToSides(), _hero->getDesiredPosition().x));
    float posY = MIN(2.9 * _tileMap->getTileSize().height+ADDY + _hero->getCenterToBottom(),MAX(_hero->getCenterToBottom()+ADDY, _hero->getDesiredPosition().y));
    _hero->setPosition(ccp(posX, posY));
    
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_monsters, pObject)
    {
        Monster *monster = (Monster*)pObject;
        posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - monster->getCenterToSides(),MAX(monster->getCenterToSides(), monster->getDesiredPosition().x));
        posY = MIN(3 * _tileMap->getTileSize().height+ADDY + monster->getCenterToBottom(),MAX(monster->getCenterToBottom()+ADDY, monster->getDesiredPosition().y));
        monster->setPosition(ccp(posX, posY));
    }
    
    CCObject *girlObject = NULL;
    CCARRAY_FOREACH(_fireGirlArr, girlObject)
    {
        FireGirl *girls = (FireGirl*)girlObject;
        posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - girls->getCenterToSides(),MAX(girls->getCenterToSides(), girls->getDesiredPosition().x));
        posY = MIN(3 * _tileMap->getTileSize().height+ADDY + girls->getCenterToBottom(),MAX(girls->getCenterToBottom()+ADDY, girls->getDesiredPosition().y));
        girls->setPosition(ccp(posX, posY));
    }
    
    CCObject *outObject = NULL;
    CCARRAY_FOREACH(_outMonsterArr, outObject)
    {
        Monster *monster = (Monster*)outObject;
        posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - monster->getCenterToSides(),MAX(monster->getCenterToSides(), monster->getDesiredPosition().x));
        posY = MIN(3 * _tileMap->getTileSize().height+ADDY + monster->getCenterToBottom(),MAX(monster->getCenterToBottom()+ADDY, monster->getDesiredPosition().y));
        monster->setPosition(ccp(posX, posY));
    }
    
    CCObject *qObject = NULL;
    CCARRAY_FOREACH(_boss, qObject)
    {
        Boss *bBoss = (Boss*)qObject;
        posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - bBoss->getCenterToSides(),MAX(bBoss->getCenterToSides(), bBoss->getDesiredPosition().x));
        posY = MIN(3 * _tileMap->getTileSize().height+ADDY + bBoss->getCenterToBottom(),MAX(bBoss->getCenterToBottom()+ADDY, bBoss->getDesiredPosition().y));
        bBoss->setPosition(ccp(posX, posY));
    }
    
    CCObject *bigSLM_object = NULL;
    CCARRAY_FOREACH(_SLM_1_Arr, bigSLM_object)
    {
        SLM_BIG *bigSLM = (SLM_BIG*)bigSLM_object;
        posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - bigSLM->getCenterToSides(),MAX(bigSLM->getCenterToSides(), bigSLM->getDesiredPosition().x));
        posY = MIN(3 * _tileMap->getTileSize().height+ADDY + bigSLM->getCenterToBottom(),MAX(bigSLM->getCenterToBottom()+ADDY, bigSLM->getDesiredPosition().y));
        bigSLM->setPosition(ccp(posX, posY));
    }
    
    CCObject *middleSLM_object = NULL;
    CCARRAY_FOREACH(_SLM_2_Arr, middleSLM_object)
    {
        SLM_MIDDLE *middleSLM = (SLM_MIDDLE*)middleSLM_object;
        posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - middleSLM->getCenterToSides(),MAX(middleSLM->getCenterToSides(), middleSLM->getDesiredPosition().x));
        posY = MIN(3 * _tileMap->getTileSize().height+ADDY + middleSLM->getCenterToBottom(),MAX(middleSLM->getCenterToBottom()+ADDY, middleSLM->getDesiredPosition().y));
        middleSLM->setPosition(ccp(posX, posY));
    }
    
    CCObject *smallSLM_object = NULL;
    CCARRAY_FOREACH(_SLM_3_Arr, smallSLM_object)
    {
        SLM_SMALL *smallSLM = (SLM_SMALL*)smallSLM_object;
        posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - smallSLM->getCenterToSides(),MAX(smallSLM->getCenterToSides(), smallSLM->getDesiredPosition().x));
        posY = MIN(3 * _tileMap->getTileSize().height+ADDY + smallSLM->getCenterToBottom(),MAX(smallSLM->getCenterToBottom()+ADDY, smallSLM->getDesiredPosition().y));
        smallSLM->setPosition(ccp(posX, posY));
    }
    
    CCObject *tBBoss_object = NULL;
    CCARRAY_FOREACH(_tBossArr, tBBoss_object)
    {
        tBoss *tBBoss = (tBoss*)tBBoss_object;
        posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - tBBoss->getCenterToSides(),MAX(tBBoss->getCenterToSides(), tBBoss->getDesiredPosition().x));
        posY = MIN(3 * _tileMap->getTileSize().height+ADDY + tBBoss->getCenterToBottom(),MAX(tBBoss->getCenterToBottom()+ADDY, tBBoss->getDesiredPosition().y));
        tBBoss->setPosition(ccp(posX, posY));
    }
}
//地图跟着英雄位置改变
void BiBiLayer::setViewpointCenter(CCPoint position)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
    CCPoint actualPosition = ccp(x, y);
    
    CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
    CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(viewPoint);
}
//添加z轴
void BiBiLayer::reorderActors()
{
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_actors->getChildren(), pObject)
    {
        BiBiAction *bibiAction = (BiBiAction*)pObject;
       // bibiAction->retain();

        float temp = bibiAction->getContentSize().height  / 2;
//        CCLog("=======%f",temp);
    
        _actors->reorderChild(bibiAction, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - bibiAction->getPosition().y + temp);
    }
}

/*
//触碰发子弹
void BiBiLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    
    if (_hero->getActionState() != kActionStateKnockedOut) {
        CCSprite *projectile = (CCSprite *)FireArr->objectAtIndex(numFire);
        int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("num");
        if (_hero->a == 2) {
            if (num == 1) {
                 projectile->setPosition(ccp(_hero->getPosition().x-20, _hero->getPosition().y-24));
            }else if(num == 2){
                 projectile->setPosition(ccp(_hero->getPosition().x-20, _hero->getPosition().y-20));
            }
//            projectile->setScale(-1);
        }else{
            if (num == 1) {
                projectile->setPosition(ccp(_hero->getPosition().x+20, _hero->getPosition().y-24));
            }else if(num == 2){
                projectile->setPosition(ccp(_hero->getPosition().x+20, _hero->getPosition().y-20));
            }
            
//            projectile->setScale(1);
        }
        numFire++;
        projectile->setVisible(true);
        if (numFire >= FireArr->count()) {
            numFire = 0;
        }
        
        CCFadeIn *fadein = CCFadeIn::create(0);
        CCMoveBy *move1 = CCMoveBy::create(1, ccp(200, 0));
        CCMoveBy *fmove1 = CCMoveBy::create(1, ccp(-200, 0));
        CCMoveBy *move2 = CCMoveBy::create(1, ccp(120, 0));
        CCMoveBy *fmove2 = CCMoveBy::create(1, ccp(-120, 0));
        CCFadeOut *fade = CCFadeOut::create(0);
        CCMoveTo *moveback = CCMoveTo::create(0, ccp(460, 300));
        CCFiniteTimeAction *FireAction;
                
        if (_hero->a == 2) {
            if (num == 1) {
                FireAction = CCSequence::create(fadein,fmove1,fade,moveback,NULL);
            }else if(num == 2){
                FireAction = CCSequence::create(fadein,fmove2,fade,moveback,NULL);
            }
            
        }else{
            if (num == 1) {
                FireAction = CCSequence::create(fadein,move1,fade,moveback,NULL);
            }else if(num == 2){
                FireAction = CCSequence::create(fadein,move2,fade,moveback,NULL);
            }
        }
        projectile->runAction(FireAction);
    }
    
//    _projectile->attack();
}
 */

#pragma mark - AI
void BiBiLayer::updateMonsters(float dt)
{
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_monsters, pObject)
    {
        Monster *monster = (Monster*)pObject;
        monster->update(dt);
        if (monster->getActionState() != kActionStateKnockedOut)
        {
            //1
            alive++;
            
            //2
            if (CURTIME > monster->getNextDecisionTime())
            {
                distanceSQ = ccpDistanceSQ(ccp( monster->getPosition().x, monster->getPosition().y-10), ccp(_hero->getPosition().x, _hero->getPosition().y-30) );
                
                if (_hero->getActionState() == kActionStateKnockedOut || ifWin > 0) {
                    monster->idle();
                }
                
                else if (distanceSQ <= 5 * 20)
                {
                    monster->setNextDecisionTime(CURTIME + frandom_range(0.1, 0.5) * 1000);
                    randomChoice = random_range(0, 1);
                    
                    if (randomChoice == 0)
                    {
                        if (_hero->getPosition().x > monster->getPosition().x)
                        {
                            monster->setScaleX(1.0);
                        }
                        else
                        {
                            monster->setScaleX(-1.0);
                        }
                        
                        //4
                        monster->setNextDecisionTime(monster->getNextDecisionTime() + frandom_range(0.1, 0.5) * 2000);
                        monster->attack();
                        if (monster->getActionState() == kActionStateAttack)
                        {
//                            if (fabsf(_hero->getPosition().y - monster->getPosition().y) < 50)
                            if (_hero->getHitbox().actual.intersectsRect(monster->getAttackbox().actual))
//                            if (collisionWithCircle(ccp(monster->getPosition().x - 5, monster->getPosition().y) , 30, ccp(_hero->getPosition().x,_hero->getPosition().y-10), 30))
                            {
                                if (_hero->getHitbox().actual.intersectsRect(monster->getAttackbox().actual))
                                {
                                    //ifBoss = 0 代表英雄
                                    CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 0);
                                    _hero->hurtWithDamage(monster->getDamage());
                                    _joyS->deleteTitleSprites((int) (monster->getDamage()));
                                }
                            }
                        }
                    }
                    else
                    {
                        monster->idle();
                    }
                }
                else if (distanceSQ <= SCREEN.width * SCREEN.width)
                {
                    //5
                    monster->setNextDecisionTime(CURTIME + frandom_range(0.2, 1.0) * 50);
                    randomChoice = random_range(0, 2);
                    if (randomChoice == 0 || randomChoice == 1)
                    {
                        CCPoint moveDirection = ccpNormalize(ccpSub(ccp(_hero->getPosition().x, _hero->getPosition().y - _hero->getCenterToBottom()) ,ccp(monster->getPosition().x, monster->getPosition().y - monster->getCenterToBottom())));
                        monster->walkWithDirection(moveDirection);
                    }else{
                        monster->idle();
                    }
                }
            }
        }
    }
}

void BiBiLayer::updateFireGirl(float dt)
{
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_fireGirlArr, pObject)
    {
        FireGirl *girls = (FireGirl*)pObject;
        girls->update(dt);
        if (girls->getActionState() != kActionStateKnockedOut)
        {
            //1
            alive++;
            
            //2
            if (CURTIME > girls->getNextDecisionTime())
            {
                distanceSQ = ccpDistanceSQ(ccp(girls->getPosition().x,girls->getPosition().y-30), ccp(_hero->getPosition().x,_hero->getPosition().y-30));
                if (_hero->getPosition().x > girls->getPosition().x)
                {
                    girls->setScaleX(1.0);
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("girlFX", 1);
                }
                else
                {
                    girls->setScaleX(-1.0);
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("girlFX", 2);
                }
                
                if (_hero->getActionState() == kActionStateKnockedOut || ifWin > 0) {
                    girls->idle();
                }else if (distanceSQ <= SCREEN.width * SCREEN.width){
                    //5
                    girls->setNextDecisionTime(CURTIME + frandom_range(0.5, 1.0) * 2000);
                    randomChoice = random_range(0, 4);
                    if (randomChoice == 0){
                        girls->attack();
                        if (girls->getActionState() == kActionStateAttack) {
                            this->GirlFire();
                        }
                }else{
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("ifGirl", 1);
                    CCPoint moveDirection = ccpNormalize(ccpSub(ccp(_hero->getPosition().x, _hero->getPosition().y - _hero->getCenterToBottom() +3) ,ccp(girls->getPosition().x, girls->getPosition().y - girls->getCenterToBottom())));
                    girls->walkWithDirection(moveDirection);
                    }
                }
            }
        }
    }
    tempBoss = alive;
}

void BiBiLayer::updateBigSLM(float dt)
{
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_SLM_1_Arr, pObject)
    {
        SLM_BIG *bigSLM = (SLM_BIG*)pObject;
        bigSLM->update(dt);
        if (bigSLM->getActionState() != kActionStateKnockedOut)
        {
            //1
            alive++;
            
            //2
            if (CURTIME > bigSLM->getNextDecisionTime())
            {
                distanceSQ = ccpDistanceSQ(ccp( bigSLM->getPosition().x, bigSLM->getPosition().y-45), ccp(_hero->getPosition().x, _hero->getPosition().y-30) );
                
                if (_hero->getActionState() == kActionStateKnockedOut || ifWin > 0) {
                    bigSLM->idle();
                }else if (distanceSQ <= SCREEN.width * SCREEN.width)
                {
                    //5
                    bigSLM->setNextDecisionTime(CURTIME + frandom_range(0.5, 1) * 1000);
                    randomChoice = random_range(0, 2);
                    if (randomChoice == 0 || randomChoice == 1)
                    {
                        CCPoint moveDirection = ccpNormalize(ccpSub(ccp(_hero->getPosition().x, _hero->getPosition().y - _hero->getCenterToBottom()) ,ccp(bigSLM->getPosition().x, bigSLM->getPosition().y - bigSLM->getCenterToBottom())));
                        bigSLM->walkWithDirection(moveDirection);
                        if (collisionWithCircle(ccp(bigSLM->getPosition().x, bigSLM->getPosition().y-10) , 40, ccp(_hero->getPosition().x,_hero->getPosition().y-10), 30)){
                            bigSLM->attack();
                            if (bigSLM->getActionState() == kActionStateAttack) {
                                //ifBoss = 0 代表英雄
                                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 0);
                                _hero->hurtWithDamage(bigSLM->getDamage());
                                _joyS->deleteTitleSprites((int) (bigSLM->getDamage()));
                            }
                        }
                    }else{
                        bigSLM->idle();
                    }
                }
            }
        }
    }
}

void BiBiLayer::updateMiddleSLM(float dt)
{
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_SLM_2_Arr, pObject)
    {
        SLM_MIDDLE *middleSLM = (SLM_MIDDLE*)pObject;
        middleSLM->update(dt);
        if (middleSLM->getActionState() != kActionStateKnockedOut)
        {
            //1
            alive++;
            
            //2
            if (CURTIME > middleSLM->getNextDecisionTime())
            {
                distanceSQ = ccpDistanceSQ(ccp( middleSLM->getPosition().x, middleSLM->getPosition().y-35), ccp(_hero->getPosition().x, _hero->getPosition().y-30) );
                
                if (_hero->getActionState() == kActionStateKnockedOut || ifWin > 0) {
                    middleSLM->idle();
                }else if (distanceSQ <= SCREEN.width * SCREEN.width)
                {
                    //5
                    middleSLM->setNextDecisionTime(CURTIME + frandom_range(0.5, 1) * 1000);
                    randomChoice = random_range(0, 2);
                    if (randomChoice == 0 || randomChoice == 1)
                    {
                        CCPoint moveDirection = ccpNormalize(ccpSub(ccp(_hero->getPosition().x, _hero->getPosition().y - _hero->getCenterToBottom()) ,ccp(middleSLM->getPosition().x, middleSLM->getPosition().y - middleSLM->getCenterToBottom())));
                        middleSLM->walkWithDirection(moveDirection);
                        if (collisionWithCircle(ccp(middleSLM->getPosition().x, middleSLM->getPosition().y-10) , 30, ccp(_hero->getPosition().x,_hero->getPosition().y-10), 30)){
                            middleSLM->attack();
                            if (middleSLM->getActionState() == kActionStateAttack) {
                                //ifBoss = 0 代表英雄
                                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 0);
                                _hero->hurtWithDamage(middleSLM->getDamage());
                                _joyS->deleteTitleSprites((int) (middleSLM->getDamage()));
                            }
                        }
                    }else{
                        middleSLM->idle();
                    }
                }
            }
        }
    }
}

void BiBiLayer::updateSmallSLM(float dt)
{
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_SLM_3_Arr, pObject)
    {
        SLM_SMALL *smallSLM = (SLM_SMALL*)pObject;
        smallSLM->update(dt);
        if (smallSLM->getActionState() != kActionStateKnockedOut)
        {
            //1
            alive++;
            
            //2
            if (CURTIME > smallSLM->getNextDecisionTime())
            {
                distanceSQ = ccpDistanceSQ(ccp( smallSLM->getPosition().x, smallSLM->getPosition().y-20), ccp(_hero->getPosition().x, _hero->getPosition().y-30) );
                
                if (_hero->getActionState() == kActionStateKnockedOut || ifWin > 0) {
                    smallSLM->idle();
                }else if (distanceSQ <= SCREEN.width * SCREEN.width)
                {
                    //5
                    smallSLM->setNextDecisionTime(CURTIME + frandom_range(0.5, 1) * 1000);
                    randomChoice = random_range(0, 2);
                    if (randomChoice == 0 || randomChoice == 1)
                    {
                        CCPoint moveDirection = ccpNormalize(ccpSub(ccp(_hero->getPosition().x, _hero->getPosition().y - _hero->getCenterToBottom()) ,ccp(smallSLM->getPosition().x, smallSLM->getPosition().y - smallSLM->getCenterToBottom())));
                        smallSLM->walkWithDirection(moveDirection);
                        if (collisionWithCircle(ccp(smallSLM->getPosition().x, smallSLM->getPosition().y) , 20, ccp(_hero->getPosition().x,_hero->getPosition().y-10), 30)){
                            smallSLM->attack();
                            if (smallSLM->getActionState() == kActionStateAttack) {
                                //ifBoss = 0 代表英雄
                                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 0);
                                _hero->hurtWithDamage(smallSLM->getDamage());
                                _joyS->deleteTitleSprites((int) (smallSLM->getDamage()));
                            }
                        }
                    }else{
                        smallSLM->idle();
                    }
                }
            }
        }
    }
}


void BiBiLayer::updateOutMonsters(float dt)
{
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_outMonsterArr, pObject)
    {
        Monster *monster = (Monster*)pObject;
        monster->update(dt);
        if (monster->getActionState() != kActionStateKnockedOut)
        {
            //1
            alive++;
            
            //2
            if (CURTIME > monster->getNextDecisionTime())
            {
                distanceSQ = ccpDistanceSQ(ccp( monster->getPosition().x, monster->getPosition().y-10), ccp(_hero->getPosition().x, _hero->getPosition().y-30) );
                
                if (_hero->getActionState() == kActionStateKnockedOut || ifWin > 0) {
                    monster->idle();
                }
                
                else if (distanceSQ <= 5 * 20)
                {
                    monster->setNextDecisionTime(CURTIME + frandom_range(0.1, 0.5) * 1000);
                    randomChoice = random_range(0, 1);
                    
                    if (randomChoice == 0)
                    {
                        if (_hero->getPosition().x > monster->getPosition().x)
                        {
                            monster->setScaleX(1.0);
                        }
                        else
                        {
                            monster->setScaleX(-1.0);
                        }
                        
                        //4
                        monster->setNextDecisionTime(monster->getNextDecisionTime() + frandom_range(0.1, 0.5) * 2000);
                        monster->attack();
                        if (monster->getActionState() == kActionStateAttack)
                        {
                            //                            if (fabsf(_hero->getPosition().y - monster->getPosition().y) < 50)
                            if (_hero->getHitbox().actual.intersectsRect(monster->getAttackbox().actual))
                                //                            if (collisionWithCircle(ccp(monster->getPosition().x - 5, monster->getPosition().y) , 30, ccp(_hero->getPosition().x,_hero->getPosition().y-10), 30))
                            {
                                if (_hero->getHitbox().actual.intersectsRect(monster->getAttackbox().actual))
                                {
                                    CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 0);
                                    _hero->hurtWithDamage(monster->getDamage());
                                    _joyS->deleteTitleSprites((int) (monster->getDamage()));
                                }
                            }
                        }
                    }
                    else
                    {
                        monster->idle();
                    }
                }
                else if (distanceSQ <= SCREEN.width * SCREEN.width)
                {
                    //5
                    monster->setNextDecisionTime(CURTIME + frandom_range(0.2, 1.0) * 50);
                    randomChoice = random_range(0, 2);
                    if (randomChoice == 0 || randomChoice == 1)
                    {
                        CCPoint moveDirection = ccpNormalize(ccpSub(ccp(_hero->getPosition().x, _hero->getPosition().y - _hero->getCenterToBottom()) ,ccp(monster->getPosition().x, monster->getPosition().y - monster->getCenterToBottom())));
                        monster->walkWithDirection(moveDirection);
                    }else{
                        monster->idle();
                    }
                }
            }
        }
    }
}


void BiBiLayer::updateBoss(float dt)
{
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_boss, pObject)
    {
        Boss *bBoss = (Boss*)pObject;
        bBoss->update(dt);
        if (bBoss->getActionState() != kActionStateKnockedOut)
        {
            //1
            alive++;
            
            //2
            if (CURTIME > bBoss->getNextDecisionTime())
            {
                distanceSQ = ccpDistanceSQ(ccp(bBoss->getPosition().x,bBoss->getPosition().y-60), ccp(_hero->getPosition().x,_hero->getPosition().y-30));
                
                if (_hero->getPosition().x > bBoss->getPosition().x)
                {
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("bossFX", 1);
                    bBoss->setScaleX(1.0);
                }else{
                    CCUserDefault::sharedUserDefault()->setIntegerForKey("bossFX", 2);
                    bBoss->setScaleX(-1.0);
                }
                
                if (_hero->getActionState() == kActionStateKnockedOut) {
                    bBoss->idle();
                }else if (distanceSQ <= 30 * 70){
                    bBoss->setNextDecisionTime(CURTIME + frandom_range(0.1, 0.5) * 1000);
                    randomChoice = random_range(0, 2);
                    
                    if (randomChoice == 0 || randomChoice == 1)
                    {
                        
                        //4
                        bBoss->setNextDecisionTime(bBoss->getNextDecisionTime() + frandom_range(0.1, 0.5) * 2000);
                        bBoss->attack();
                        if (bBoss->getActionState() == kActionStateAttack)
                        {
//                            if (fabsf(_hero->getPosition().y +30 - bBoss->getPosition().y) < 50)
//                            {
//                                if (_hero->getHitbox().actual.intersectsRect(bBoss->getAttackbox().actual))
                                if (collisionWithCircle(ccp(bBoss->getPosition().x-40, bBoss->getPosition().y) , 50, ccp(_hero->getPosition().x,_hero->getPosition().y), 40))
                                {
                                    CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 0);
                                    _hero->hurtWithDamage(bBoss->getDamage());
                                    _joyS->deleteTitleSprites((int) (bBoss->getDamage()));
                                }
//                            }
                        }
                    }else{
                        bBoss->idle();
                    }
                }else if (distanceSQ <= SCREEN.width * SCREEN.width){
                    //5
                    bBoss->setNextDecisionTime(CURTIME + frandom_range(0.5, 1.0) * 100);
                    randomChoice = random_range(0, 8);
                    if (randomChoice == 0 || randomChoice == 1 || randomChoice == 2)
                    {
                        bBoss->idle();
                    }else if (randomChoice == 3){
                        this->BossFire();
                    }else{
                        CCPoint moveDirection = ccpNormalize(ccpSub(ccp(_hero->getPosition().x, _hero->getPosition().y - _hero->getCenterToBottom()) ,ccp(bBoss->getPosition().x, bBoss->getPosition().y - bBoss->getCenterToBottom())));
                        bBoss->walkWithDirection(moveDirection);
                    }
                }
            }
        }
    }
    tempBoss = alive;
}

void BiBiLayer::updateSBoss(float dt)
{
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_sBossArr, pObject)
    {
        sBoss *sbBoss = (sBoss*)pObject;
        sbBoss->update(dt);
        if (sbBoss->getActionState() != kActionStateKnockedOut)
        {
            //1
            alive++;
            
            if (sbBoss->getActionState() == kActionStateSkill) {
                int x = _tileMap->getMapSize().width*_tileMap->getTileSize().width;
                sbBoss->setPosition(ccp(x - sbBoss->getCenterToSides()-80, 90+ADDY));
//                sbBoss->setPosition(ccp(300, 70));
                
                sbBoss->idle();
                                
                int bossCount = 1;
                this->setboss(CCArray::createWithCapacity(bossCount));
                for (int i=0; i<bossCount; i++) {
                    Boss *boss = Boss::create();
                    _actors->addChild(boss);
                    _boss->addObject(boss);
                    int minX = sbBoss->getPosition().x - 50;
                    int maxX = sbBoss->getPosition().x+100;
                    int minY = boss->getCenterToBottom()+ADDY;
                    int maxY = 3 * _tileMap->getTileSize().height+ADDY + boss->getCenterToBottom();
                    boss->setScaleX(-1);
                    boss->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
                    boss->setDesiredPosition(boss->getPosition());
                    boss->idle();
                }
            }
            
            //2
            if (CURTIME > sbBoss->getNextDecisionTime())
            {
                distanceSQ = ccpDistanceSQ(ccp(sbBoss->getPosition().x,sbBoss->getPosition().y), ccp(_hero->getPosition().x,_hero->getPosition().y));
                
                if (_hero->getActionState() == kActionStateKnockedOut) {
                    sbBoss->idle();
                }else if (distanceSQ <= 200 * 300){
                    sbBoss->setNextDecisionTime(CURTIME + frandom_range(1, 2) * 2000);
                    randomChoice = random_range(0,1);
                    
                    if (sbBoss->getHpCount() <= 300) {
                        sBossFindBoss++;
                        if (sBossFindBoss == 1) {
                            int x = _tileMap->getMapSize().width*_tileMap->getTileSize().width;
                            CCFiniteTimeAction *sbBossAction = CCSequence::create(CCFadeOut::create(0),CCMoveTo::create(0, ccp(x - sbBoss->getCenterToSides()-80, 190+ADDY)),CCFadeIn::create(0),NULL);
//                            CCFiniteTimeAction *sbBossAction = CCSequence::create(CCFadeOut::create(0),CCMoveTo::create(0, ccp(300, 190)),CCFadeIn::create(0),NULL);
                            sbBoss->skill();
                            sbBoss->runAction(sbBossAction);
                            
                        }else if(sbBoss->getActionState() != kActionStateSkill && sbBoss->getActionState() != kActionStateAttack && outSmallSLMNum <100){
                            if (randomChoice == 0 || randomChoice == 1){
                                sbBoss->setNextDecisionTime(sbBoss->getNextDecisionTime() + frandom_range(1, 2) * 2000);
                                sbBoss->attack();
                                if (sbBoss->getActionState() == kActionStateAttack)
                                {
                                    int outMonsterCount = 1;
                                    outSmallSLMNum = outSmallSLMNum + outMonsterCount;
                                    for (int i = 0; i < outMonsterCount; i++)
                                    {
                                        
                                        SLM_MIDDLE *middleSLM = SLM_MIDDLE::create();
                                        _actors->addChild(middleSLM);
                                        _SLM_2_Arr->addObject(middleSLM);
                                        
                                        int minX = sbBoss->getPosition().x - 100;
                                        int maxX = sbBoss->getPosition().x;
                                        int minY = middleSLM->getCenterToBottom()+ADDY;
                                        int maxY = 3 * _tileMap->getTileSize().height+ADDY + middleSLM->getCenterToBottom();
                                        middleSLM->setScaleX(-1);
                                        middleSLM->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
                                        middleSLM->setDesiredPosition(middleSLM->getPosition());
                                        middleSLM->idle();
                                    }
                                }
                            }
                        }
                    }else if ((randomChoice == 0 || randomChoice == 1 )&& outMonsterNum < 100){
                        sbBoss->setNextDecisionTime(sbBoss->getNextDecisionTime() + frandom_range(0.1, 0.5) * 2000);
                        sbBoss->attack();
                        if (sbBoss->getActionState() == kActionStateAttack)
                        {
                            int outMonsterCount = random_range(1, 3);
                            outMonsterNum = outMonsterNum + outMonsterCount;
                            
                            for (int i = 0; i < outMonsterCount; i++)
                            {
                                Monster *monster = Monster::create();
                                _actors->addChild(monster);
                                _outMonsterArr->addObject(monster);
                                
                                int minX = sbBoss->getPosition().x - 100;
                                int maxX;
                                if (sbBoss->getPosition().x+100>_tileMap->getMapSize().width * _tileMap->getTileSize().width - monster->getCenterToSides()) {
                                    maxX = _tileMap->getMapSize().width * _tileMap->getTileSize().width - monster->getCenterToSides();
                                }else{
                                    maxX = sbBoss->getPosition().x+100;
                                }
                                int minY = monster->getCenterToBottom()+ADDY;
                                int maxY = 3 * _tileMap->getTileSize().height+ADDY+ monster->getCenterToBottom();
                                monster->setScaleX(-1);
                                monster->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
                                monster->setDesiredPosition(monster->getPosition());
                                monster->idle();
                            }
                        }
                    }
                }
            }
        }
    }
    tempSBoss = alive;
}

void BiBiLayer::updateTBoss(float dt)
{
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_tBossArr, pObject)
    {
        tBoss *tBBoss = (tBoss*)pObject;
        tBBoss->update(dt);
        if (tBBoss->getActionState() != kActionStateKnockedOut)
        {
            //1
            alive++;
            
            //2
            if (CURTIME > tBBoss->getNextDecisionTime())
            {
                distanceSQ = ccpDistanceSQ(ccp( tBBoss->getPosition().x, tBBoss->getPosition().y-95), ccp(_hero->getPosition().x, _hero->getPosition().y-30) );
                
                if (_hero->getActionState() == kActionStateKnockedOut || ifWin > 0) {
                    tBBoss->idle();
                }else if (distanceSQ <= SCREEN.width * SCREEN.width)
                {
                    //5
                    tBBoss->setNextDecisionTime(CURTIME + frandom_range(0.5, 1) * 1000);
                    randomChoice = random_range(0, 2);
                    if (randomChoice == 0 || randomChoice == 1)
                    {
                        CCPoint moveDirection = ccpNormalize(ccpSub(ccp(_hero->getPosition().x, _hero->getPosition().y - _hero->getCenterToBottom()) ,ccp(tBBoss->getPosition().x, tBBoss->getPosition().y - tBBoss->getCenterToBottom())));
                        tBBoss->walkWithDirection(moveDirection);
                        if (collisionWithCircle(ccp(tBBoss->getPosition().x, tBBoss->getPosition().y-10) , 90, ccp(_hero->getPosition().x,_hero->getPosition().y-10), 30)){
                            if (distanceSQ <= 30 * 100){
                                tBBoss->attack();
                            }
                            
                            if (tBBoss->getActionState() == kActionStateAttack) {
                                //ifBoss = 0 代表英雄
                                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 0);
                                _hero->hurtWithDamage(tBBoss->getDamage());
                                _joyS->deleteTitleSprites((int) (tBBoss->getDamage()));
                            }
                        }
                    }else{
                        tBBoss->idle();
                    }
                }
            }
        }
    }
    tempTBoss = alive;
}

void BiBiLayer::BossFire()
{
    int numboss = CCUserDefault::sharedUserDefault()->getIntegerForKey("bossFX");
    CCSprite *_bBoss = (CCSprite *)_boss->objectAtIndex(0);
    
    CCSprite *projectile = (CCSprite *)BossFireArr->objectAtIndex(numBossFire);
    projectile->setPosition(ccp(_bBoss->getPosition().x, _bBoss->getPosition().y-30));
    if (numboss == 1) {
        projectile->setScaleX(-1);
    }else{
        projectile->setScaleX(1);
    }
    numBossFire++;
    projectile->setVisible(true);
    if (numBossFire >= BossFireArr->count()) {
        numBossFire = 0;
    }
    
    CCFadeIn *fadein = CCFadeIn::create(0);
    CCMoveBy *move1 = CCMoveBy::create(2.5, ccp(400, 0));
    CCMoveBy *fmove1 = CCMoveBy::create(2.5, ccp(-400, 0));
    CCFadeOut *fade = CCFadeOut::create(0);
    CCMoveTo *moveback = CCMoveTo::create(0, ccp(460, 300));
    CCFiniteTimeAction *FireAction;
    
    if (numboss == 1){
        FireAction = CCSequence::create(fadein,move1,fade,moveback,NULL);
    }else{
        FireAction = CCSequence::create(fadein,fmove1,fade,moveback,NULL);
        }
    projectile->runAction(FireAction);
}

void BiBiLayer::GirlFire()
{
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(_fireGirlArr, pObject)
    {
        FireGirl *fireGirl = (FireGirl*)pObject;
//        CCLOG("--------%d",_fireGirlArr->count());
//        CCLOG("--------%d",fireGirlFireArr->count());
        CCSprite *projectile = (CCSprite *)fireGirlFireArr->objectAtIndex(numFireGirlFire);
        projectile->setPosition(ccp(fireGirl->getPosition().x, fireGirl->getPosition().y));
        numFireGirlFire++;
        projectile->setVisible(true);
        if (numFireGirlFire >= fireGirlFireArr->count()) {
            numFireGirlFire = 0;
        }
        
        CCFadeIn *fadein = CCFadeIn::create(0);
        CCMoveBy *move1 = CCMoveBy::create(1.2, ccp(300, 0));
        CCMoveBy *fmove1 = CCMoveBy::create(1.2, ccp(-300, 0));
        CCFadeOut *fade = CCFadeOut::create(0);
        CCMoveTo *moveback = CCMoveTo::create(0, ccp(460, 300));
        CCFiniteTimeAction *FireAction;
        
        int girlFX = CCUserDefault::sharedUserDefault()->getIntegerForKey("girlFX");
        if (girlFX == 1){
            FireAction = CCSequence::create(fadein,move1,fade,moveback,NULL);
        }else{
            FireAction = CCSequence::create(fadein,fmove1,fade,moveback,NULL);
        }
        projectile->runAction(FireAction);
    
    }
}


#pragma mark - 子弹触碰判断
void BiBiLayer::updateHeroProjectile(float dt)
{
    CCArray *projectilesToDelete = CCArray::create();
    int num = CCUserDefault::sharedUserDefault()->getIntegerForKey("num");
    CCObject *pObject = NULL;
    CCObject *pObject2 = NULL;//monster
    CCObject *pObject3 = NULL;//boss
    CCObject *pObject4 = NULL;//sboss
    CCObject *pObject5 = NULL;//outmonster
    CCObject *pObject6 = NULL;//firegirl
    CCObject *bigSLM_Object = NULL;
    CCObject *middleSLM_Object = NULL;
    CCObject *smallSLM_Object = NULL;
    CCObject *tBBoss_object = NULL;
    CCARRAY_FOREACH(FireArr, pObject)
    {
        bool anyHit = false;
        CCSprite *projectile = (CCSprite*)pObject;
        CCArray *monstersToDelete = CCArray::create();
        CCArray *fireGirlsToDelete = CCArray::create();
        CCArray *outMonstersToDelete = CCArray::create();
        CCArray *bossToDelete = CCArray::create();
        CCArray *sBossToDelete = CCArray::create();
        CCArray *bigSLMToDelete = CCArray::create();
        CCArray *middleSLMToDelete = CCArray::create();
        CCArray *smallSLMToDelete = CCArray::create();
        CCArray *tBossToDelete = CCArray::create();
        
        CCARRAY_FOREACH(_monsters, pObject2)
        {
            Monster *monster = (Monster*)pObject2;
            float projectilePy;
            int r;
            if (num == 1) {
                projectilePy = projectile->getPosition().y+13;
                r = 2;
            }else if(num == 2){
                projectilePy = projectile->getPosition().y+9;
                r = 5;
            }
            if (collisionWithCircle(ccp(projectile->getPosition().x, projectilePy) , r, ccp(monster->getPosition().x,monster->getPosition().y), 15))
//            if (projectile->boundingBox().intersectsRect(monster->getHitbox().actual))
            {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 1);
                
                monster->hurtWithDamage(_hero->getDamage());
                
                anyHit = true;
//                monster->setHpCount(monster->getHpCount()-_hero->getDamage());
                if (monster->getHpCount()<=0) {
                    monstersToDelete->addObject(monster);
                }
//                break;
            }
        }
        
        CCARRAY_FOREACH(_outMonsterArr, pObject5)
        {
            Monster *monster = (Monster*)pObject5;
            float projectilePy;
            int r;
            if (num == 1) {
                projectilePy = projectile->getPosition().y+13;
                r = 2;
            }else if(num == 2){
                projectilePy = projectile->getPosition().y+9;
                r = 5;
            }
            if (collisionWithCircle(ccp(projectile->getPosition().x, projectilePy) , r, ccp(monster->getPosition().x,monster->getPosition().y), 15))
                //            if (projectile->boundingBox().intersectsRect(monster->getHitbox().actual))
            {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 1);
                
                monster->hurtWithDamage(_hero->getDamage());
                
                anyHit = true;
                //                monster->setHpCount(monster->getHpCount()-_hero->getDamage());
                if (monster->getHpCount()<=0) {
                    outMonstersToDelete->addObject(monster);
                }
                //                break;
            }
        }
        
        CCARRAY_FOREACH(_fireGirlArr, pObject6)
        {
            FireGirl *girls = (FireGirl*)pObject6;
            float projectilePy;
            int r;
            if (num == 1) {
                projectilePy = projectile->getPosition().y+13;
                r = 2;
            }else if(num == 2){
                projectilePy = projectile->getPosition().y+9;
                r = 5;
            }
            if (collisionWithCircle(ccp(projectile->getPosition().x, projectilePy) , r, ccp(girls->getPosition().x,girls->getPosition().y), 30))
                //            if (projectile->boundingBox().intersectsRect(monster->getHitbox().actual))
            {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 2);
                
                girls->hurtWithDamage(_hero->getDamage());
                
                anyHit = true;
                //                monster->setHpCount(monster->getHpCount()-_hero->getDamage());
                if (girls->getHpCount()<=0) {
                    fireGirlsToDelete->addObject(girls);
                }
                //                break;
            }
        }
        
        CCARRAY_FOREACH(_SLM_1_Arr, bigSLM_Object)
        {
            SLM_BIG *bigSLM = (SLM_BIG*)bigSLM_Object;
            float projectilePy;
            int r;
            if (num == 1) {
                projectilePy = projectile->getPosition().y+13;
                r = 2;
            }else if(num == 2){
                projectilePy = projectile->getPosition().y+9;
                r = 5;
            }
            if (collisionWithCircle(ccp(projectile->getPosition().x, projectilePy) , r, ccp(bigSLM->getPosition().x,bigSLM->getPosition().y), 45))
            {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 3);
                
                bigSLM->hurtWithDamage(_hero->getDamage());
                
                anyHit = true;
                if (bigSLM->getHpCount()<=0) {
                    bigSLMToDelete->addObject(bigSLM);
                }
            }
        }

        CCARRAY_FOREACH(_SLM_2_Arr, middleSLM_Object)
        {
            SLM_MIDDLE *middleSLM = (SLM_MIDDLE*)middleSLM_Object;
            float projectilePy;
            int r;
            if (num == 1) {
                projectilePy = projectile->getPosition().y+13;
                r = 2;
            }else if(num == 2){
                projectilePy = projectile->getPosition().y+9;
                r = 5;
            }
            if (collisionWithCircle(ccp(projectile->getPosition().x, projectilePy) , r, ccp(middleSLM->getPosition().x,middleSLM->getPosition().y), 35))
            {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 4);
                
                middleSLM->hurtWithDamage(_hero->getDamage());
                
                anyHit = true;
                if (middleSLM->getHpCount()<=0) {
                    middleSLMToDelete->addObject(middleSLM);
                }
            }
        }

        CCARRAY_FOREACH(_SLM_3_Arr, smallSLM_Object)
        {
            SLM_SMALL *smallSLM = (SLM_SMALL*)smallSLM_Object;
            float projectilePy;
            int r;
            if (num == 1) {
                projectilePy = projectile->getPosition().y+13;
                r = 2;
            }else if(num == 2){
                projectilePy = projectile->getPosition().y+9;
                r = 5;
            }
            if (collisionWithCircle(ccp(projectile->getPosition().x, projectilePy) , r, ccp(smallSLM->getPosition().x,smallSLM->getPosition().y), 20))
            {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 5);
                
                smallSLM->hurtWithDamage(_hero->getDamage());
                
                anyHit = true;
                if (smallSLM->getHpCount()<=0) {
                    smallSLMToDelete->addObject(smallSLM);
                }
            }
        }
        
        CCARRAY_FOREACH(_boss, pObject3)
        {
            Boss *bBoss = (Boss *)pObject3;
            float projectilePy;
            int r;
            if (num == 1) {
                projectilePy = projectile->getPosition().y + 13;
                r = 2;
            }else if(num == 2){
                projectilePy = projectile->getPosition().y + 9;
                r = 5;
            }
            if (collisionWithCircle(ccp(projectile->getPosition().x,projectilePy) , r, ccp(bBoss->getPosition().x,bBoss->getPosition().y-5), 40))
//            if (projectile->boundingBox().intersectsRect(bBoss->getHitbox().actual))
            {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 10);
                
                bBoss->hurtWithDamage(_hero->getDamage());
                anyHit = true;
                
                if (bBoss->getHpCount()<=0) {
                    bossToDelete->addObject(bBoss);
                }
            }
        }
        
        CCARRAY_FOREACH(_sBossArr, pObject4)
        {
            sBoss *sbBoss = (sBoss *)pObject4;
            float projectilePy;
            int r;
            if (num == 1) {
                projectilePy = projectile->getPosition().y + 13;
                r = 2;
            }else if(num == 2){
                projectilePy = projectile->getPosition().y + 9;
                r = 5;
            }
            if (collisionWithCircle(ccp(projectile->getPosition().x,projectilePy) , r, ccp(sbBoss->getPosition().x,sbBoss->getPosition().y-5), 30))
                //            if (projectile->boundingBox().intersectsRect(bBoss->getHitbox().actual))
            {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 11);
                
                sbBoss->hurtWithDamage(_hero->getDamage());
                anyHit = true;
                
                if (sbBoss->getHpCount()<=0) {
                    sBossToDelete->addObject(sbBoss);
                }
            }
        }
        
        CCARRAY_FOREACH(_tBossArr, tBBoss_object)
        {
            tBoss *tBBoss = (tBoss*)tBBoss_object;
            float projectilePy;
            int r;
            if (num == 1) {
                projectilePy = projectile->getPosition().y+13;
                r = 2;
            }else if(num == 2){
                projectilePy = projectile->getPosition().y+9;
                r = 5;
            }
            if (collisionWithCircle(ccp(projectile->getPosition().x, projectilePy) , r, ccp(tBBoss->getPosition().x,tBBoss->getPosition().y-10), 90))
            {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 12);
                
                tBBoss->hurtWithDamage(_hero->getDamage());
                
                int randnum = random_range(0, 19);
                
                if (randnum == 19) {
                    SLM_BIG *bigSLM = SLM_BIG::create();
                    _actors->addChild(bigSLM);
                    _SLM_1_Arr->addObject(bigSLM);
                    
                    int minX = tBBoss->getPosition().x-100;
                    int maxX = tBBoss->getPosition().x+100;
                    int minY = tBBoss->getPosition().y-100;
                    int maxY = tBBoss->getPosition().y+100;
                    bigSLM->setScaleX(-1);
                    bigSLM->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
                    bigSLM->setDesiredPosition(bigSLM->getPosition());
                    bigSLM->idle();
                }else if (randnum == 18 || randnum == 17 || randnum == 16 || randnum == 15){
                    SLM_MIDDLE *middleSLM = SLM_MIDDLE::create();
                    _actors->addChild(middleSLM);
                    _SLM_2_Arr->addObject(middleSLM);
                    
                    int minX = tBBoss->getPosition().x-100;
                    int maxX = tBBoss->getPosition().x+100;
                    int minY = tBBoss->getPosition().y-100;
                    int maxY = tBBoss->getPosition().y+100;
                    middleSLM->setScaleX(-1);
                    middleSLM->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
                    middleSLM->setDesiredPosition(middleSLM->getPosition());
                    middleSLM->idle();
                }else{
                    SLM_SMALL *smallSLM = SLM_SMALL::create();
                    _actors->addChild(smallSLM);
                    _SLM_3_Arr->addObject(smallSLM);
                    
                    int minX = tBBoss->getPosition().x-100;
                    int maxX = tBBoss->getPosition().x+100;
                    int minY = tBBoss->getPosition().y-100;
                    int maxY = tBBoss->getPosition().y+100;
                    smallSLM->setScaleX(-1);
                    smallSLM->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
                    smallSLM->setDesiredPosition(smallSLM->getPosition());
                    smallSLM->idle();
                }
                
                anyHit = true;
                if (tBBoss->getHpCount()<=0) {
                    tBossToDelete->addObject(tBBoss);
                }
            }
        }

        
        CCARRAY_FOREACH(monstersToDelete, pObject2)
        {
            CCSprite *monster = (CCSprite*)pObject2;
            _monsters->removeObject(monster);
            this->removeChild(monster, true);
        }
        
        CCARRAY_FOREACH(fireGirlsToDelete, pObject6)
        {
            CCSprite *fireGirl = (CCSprite*)pObject6;
            _fireGirlArr->removeObject(fireGirl);
            this->removeChild(fireGirl, true);
        }
        
        
        CCARRAY_FOREACH(outMonstersToDelete, pObject5)
        {
            CCSprite *monster = (CCSprite*)pObject5;
            _outMonsterArr->removeObject(monster);
            this->removeChild(monster, true);
        }
        
        CCARRAY_FOREACH(bigSLMToDelete, bigSLM_Object)
        {
            CCSprite *bigSLM = (CCSprite*)bigSLM_Object;
            
            for (int i = 0; i < 3; i++) {
                SLM_MIDDLE *middleSLM = SLM_MIDDLE::create();
                _actors->addChild(middleSLM);
                _SLM_2_Arr->addObject(middleSLM);
                
                int minX = bigSLM->getPosition().x-50;
                int maxX = bigSLM->getPosition().x+50;
                int minY = bigSLM->getPosition().y-50;
                int maxY = bigSLM->getPosition().y+50;
                middleSLM->setScaleX(-1);
                middleSLM->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
                middleSLM->setDesiredPosition(middleSLM->getPosition());
                middleSLM->idle();
            }
            
            
            _SLM_1_Arr->removeObject(bigSLM);
            this->removeChild(bigSLM, true);
        }
        
        CCARRAY_FOREACH(middleSLMToDelete, middleSLM_Object)
        {
            CCSprite *middleSLM = (CCSprite*)middleSLM_Object;
            
            for (int i = 0; i < 3; i++) {
                SLM_SMALL *smallSLM = SLM_SMALL::create();
                _actors->addChild(smallSLM);
                _SLM_3_Arr->addObject(smallSLM);
                
                int minX = middleSLM->getPosition().x-50;
                int maxX = middleSLM->getPosition().x+50;
                int minY = middleSLM->getPosition().y-50;
                int maxY = middleSLM->getPosition().y+50;
                smallSLM->setScaleX(-1);
                smallSLM->setPosition(ccp(random_range(minX, maxX), random_range(minY, maxY)));
                smallSLM->setDesiredPosition(smallSLM->getPosition());
                smallSLM->idle();
            }
            
            _SLM_2_Arr->removeObject(middleSLM);
            this->removeChild(middleSLM, true);
        }
        
        CCARRAY_FOREACH(smallSLMToDelete, smallSLM_Object)
        {
            CCSprite *smallSLM = (CCSprite*)smallSLM_Object;
            _SLM_3_Arr->removeObject(smallSLM);
            this->removeChild(smallSLM, true);
        }
        
        CCARRAY_FOREACH(bossToDelete, pObject3)
        {
            CCSprite *bBoss = (CCSprite*)pObject3;
            _boss->removeObject(bBoss);
            this->removeChild(bBoss, true);
        }
        
        CCARRAY_FOREACH(sBossToDelete, pObject4)
        {
            CCSprite *sbBoss = (CCSprite*)pObject4;
            _sBossArr->removeObject(sbBoss);
            this->removeChild(sbBoss, true);
        }
        
        CCARRAY_FOREACH(tBossToDelete, tBBoss_object)
        {
            CCSprite *tBBoss = (CCSprite*)tBBoss_object;
            _tBossArr->removeObject(tBBoss);
            this->removeChild(tBBoss, true);
        }
        
        if (anyHit)
        {
            projectilesToDelete->addObject(projectile);
//            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.wav");
        }
        
        
//        monstersToDelete->release();
    }
    
    CCARRAY_FOREACH(projectilesToDelete, pObject)
    {
        CCSprite *projectile = (CCSprite*)pObject;
        projectile->stopAllActions();
        projectile->setVisible(false);
        projectile->setPosition(ccp(460, 300));
        
//        CCFadeOut *fade = CCFadeOut::create(0);
//        CCMoveTo *moveback = CCMoveTo::create(0, ccp(460, 300));
//        CCFiniteTimeAction *action = CCSequence::create(fade,moveback,NULL);
//        projectile->runAction(action);

//        FireArr->removeObject(projectile);
//        this->removeChild(projectile, true);
    }
    
//    projectilesToDelete->release();

}

void BiBiLayer::updateBossProjectile(float dt)
{
    CCArray *projectilesToDelete = CCArray::create();
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(BossFireArr, pObject)
    {
        bool heroHit = false;
        CCSprite *projectile = (CCSprite*)pObject;
        if (collisionWithCircle(ccp(projectile->getPosition().x-3, projectile->getPosition().y+29), 1, ccp(_hero->getPosition().x, _hero->getPosition().y), 25)) {
            CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 0);
            _hero->hurtWithDamage(4);
            _joyS->deleteTitleSprites((int) (4));
            heroHit = true;
        }
        
        if (heroHit)
        {
            projectilesToDelete->addObject(projectile);
        }
    }
    
    CCARRAY_FOREACH(projectilesToDelete, pObject)
    {
        CCSprite *projectile = (CCSprite*)pObject;
        projectile->stopAllActions();
        projectile->setVisible(false);
        projectile->setPosition(ccp(460, 300));
    }

}

void BiBiLayer::updateFireGirlProjectile(float dt)
{
    CCArray *projectilesToDelete = CCArray::create();
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(fireGirlFireArr, pObject)
    {
        bool heroHit = false;
        CCSprite *projectile = (CCSprite*)pObject;
        if (collisionWithCircle(ccp(projectile->getPosition().x, projectile->getPosition().y), 1, ccp(_hero->getPosition().x, _hero->getPosition().y), 25)) {
            //ifBoss = 0 代表英雄
            CCUserDefault::sharedUserDefault()->setIntegerForKey("ifBoss", 0);
            _hero->hurtWithDamage(2);
            _joyS->deleteTitleSprites((int) (2));
            heroHit = true;
        }
        
        if (heroHit)
        {
            projectilesToDelete->addObject(projectile);
        }
    }
    
    CCARRAY_FOREACH(projectilesToDelete, pObject)
    {
        CCSprite *projectile = (CCSprite*)pObject;
        projectile->stopAllActions();
        projectile->setVisible(false);
        projectile->setPosition(ccp(460, 300));
    }
    
}


bool BiBiLayer::collisionWithCircle(CCPoint circlePoint, float radius, CCPoint circlePointTwo, float radiusTwo)
{
    float xdif = circlePoint.x - circlePointTwo.x;
    float ydif = circlePoint.y - circlePointTwo.y;
    
    float distance = sqrt(xdif * xdif + ydif * ydif);
    
    if(distance <= radius + radiusTwo)
    {
        return true;
    }
    return false;
}


void BiBiLayer::turnWinScene()
{
    this->unschedule(schedule_selector( BiBiLayer::turnWinScene));
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *winScene = WinScene::create();
    pDirector->replaceScene(winScene);
}

void BiBiLayer::turnLoseScene()
{
    this->unschedule(schedule_selector( BiBiLayer::turnWinScene));
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *loseScene = LoseScene::create();
    pDirector->replaceScene(loseScene);
}

void BiBiLayer::restartGame(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(BiBiScene::create());
}

#pragma mark - 返回菜单
void BiBiLayer::backMeun(CCObject* pSender)
{
    CCScene *meunScene = MeunScence::create();
    CCDirector::sharedDirector()->replaceScene(meunScene);
}



