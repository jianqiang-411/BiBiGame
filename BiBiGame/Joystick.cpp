//
//  Joystick.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//
//

#include "Joystick.h"
#include "BiBiScene.h"
#include "MeunScence.h"
#include "BiBiLayer.h"

using namespace cocos2d;

Joystick::Joystick()
{
    _dPad = NULL;
    _bloodArr = NULL;
    _sBlood = NULL;
    _ddPad = NULL;
}

bool Joystick::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        
        int whichlevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("Level");
        
        //第二关粒子效果
        if (whichlevel == 2) {
            this->initSnow();
        }

        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCString *strGameLevel = CCString::createWithFormat("Level %i",whichlevel);
        CCLabelTTF *GameLevel = CCLabelTTF::create(strGameLevel->getCString(), "Arial", 40);
        GameLevel->setPosition(ccp(-winSize.width/2, winSize.height/2));
        this->addChild(GameLevel,5);
        CCFadeOut *GLFadeOut_1 = CCFadeOut::create(0);
        CCMoveTo *GLMoveTo = CCMoveTo::create(0, ccp(winSize.width/2, winSize.height/2));
        CCFadeIn *GLFadeIn = CCFadeIn::create(1);
        CCMoveBy *wait = CCMoveBy::create(2, ccp(0, 0));
        CCFadeOut *GlFadeOut_2 = CCFadeOut::create(1);
        CCMoveTo *outScreen = CCMoveTo::create(0, ccp(-winSize.width/2, winSize.height/2));
        CCFiniteTimeAction *GLAction = CCSequence::create(GLFadeOut_1,GLMoveTo,GLFadeIn,wait,GlFadeOut_2,outScreen,NULL);
        GameLevel->runAction(GLAction);
        
        //暂停按钮
        CCMenuItemImage *stop = CCMenuItemImage::create("stop1.png", "stop2.png", this, menu_selector(Joystick::stop));
        stop->setPosition(ccp(460, 300));
        sMenu = CCMenu::create(stop,NULL);
        sMenu->setPosition(CCPointZero);
        this->addChild(sMenu,1);
        
        //方向键
        _dPad = SimpleDPad::dPadWithFile(CCString::create("pd_dpad.png"), 64);
        _dPad->setPosition(ccp(64.0, 64.0));
        _dPad->setOpacity(100);
        this->addChild(_dPad);
        
        //攻击键
        _ddPad = FireBTN::dPadWithFile(CCString::create("fire_btn.png"), 32);
        _ddPad->setPosition(ccp(420.0, 40.0));
        _ddPad->setOpacity(100);
        this->addChild(_ddPad);
        
        //血条
        CCSprite *blood_out = CCSprite::create("blood_out_1.png");
        blood_out->setPosition(ccp(119, 295));
        this->addChild(blood_out);
        
        _bloodArr = CCArray::create();
        _bloodArr->retain();
        this->createTitleSprites(100);
        
        
        
        //时间计时
        CCLabelTTF *timeWZ = CCLabelTTF::create("time:", "Verdana", 20);
        timeWZ->setPosition(ccp(350, 300));
        timeWZ->setColor(ccc3(0, 0, 0));
        //        timeLb->setOpacity(150);
        this->addChild(timeWZ);
        
        timeLb = CCLabelTTF::create("000", "Verdana-Bold", 20);
        timeLb->setPosition(ccp(400, 300));
        timeLb->setColor(ccc3(0, 0, 0));
//        timeLb->setOpacity(150);
        this->addChild(timeLb);

        this->schedule(schedule_selector(Joystick::timeLabel), 1);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void Joystick::stop()
{
    //是暂停按钮点击一次后不能再次按
    sMenu->setEnabled(false);
    // 使游戏暂停
    CCDirector::sharedDirector()->pause();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    stopBackground = CCSprite::create("stop_background.png");
    stopBackground->setPosition(ccp(winSize.width/2, winSize.height/2));
    stopBackground->setOpacity(150);
    this->addChild(stopBackground,3);
    //restart
    CCLabelTTF *label1 = CCLabelTTF::create("RESTART", "Arial", 25);
    CCMenuItemLabel *item1 = CCMenuItemLabel::create(label1, this, menu_selector(Joystick::restart));
    item1->setPosition(ccp(winSize.width/2, winSize.height/2+50));
    //menu
    CCLabelTTF *label2 = CCLabelTTF::create("MEUN", "Arial", 25);
    CCMenuItemLabel *item2 = CCMenuItemLabel::create(label2, this, menu_selector(Joystick::menu));
    item2->setPosition(ccp(winSize.width/2, winSize.height/2));
    //back
    CCLabelTTF *label3 = CCLabelTTF::create("BACK", "Arial", 25);
    CCMenuItemLabel *item3 = CCMenuItemLabel::create(label3, this, menu_selector(Joystick::back));
    item3->setPosition(ccp(winSize.width/2, winSize.height/2-50));
    
    pmenu = CCMenu::create(item1,item2,item3,NULL);
    pmenu->setPosition(CCPointZero);
    this->addChild(pmenu,4);
    
    
}

void Joystick::restart()
{
    //游戏暂停恢复
    CCDirector::sharedDirector()->resume();
    //激活暂停按钮
    sMenu->setEnabled(true);
    CCDirector::sharedDirector()->replaceScene(BiBiScene::create());
}

void Joystick::menu()
{
    CCDirector::sharedDirector()->resume();//游戏恢复
    CCDirector::sharedDirector()->replaceScene(MeunScence::create());
}

void Joystick::back()
{
    CCDirector::sharedDirector()->resume();//游戏恢复
    this->removeChild(pmenu, true);
    this->removeChild(stopBackground, true);
    sMenu->setEnabled(true);
}

void Joystick::createTitleSprites(int _iHpCount)
{
    for ( int i = 0; i < _iHpCount; i++) {
        _sBlood = CCSprite::create("blood_1.png");
        _sBlood->setPosition(ccp(20 + i*2, 295));
        this->addChild(_sBlood);
        _bloodArr->addObject(_sBlood);
    }
}

void Joystick::deleteTitleSprites(int _iDamage)
{
//    CCSprite *projectile = (CCSprite *)FireArr->objectAtIndex(numFire);
//    int numBlood;
    int ifiNum = iNum - _iDamage;
    if (ifiNum >=0) {
        for (int i = iNum; i>(iNum - _iDamage); i--) {
            if (_bloodArr->objectAtIndex(i) == NULL) {
                return;
            }else{
                CCSprite *_blood = (CCSprite *)_bloodArr->objectAtIndex(i);
                _bloodArr->removeObject(_blood);
                this->removeChild(_blood, true);
            }
        }
        iNum = iNum - _iDamage;
    }else{
        if (iNum >= 0) {
            for (int i = iNum; i>=0; i--) {
                CCSprite *_blood = (CCSprite *)_bloodArr->objectAtIndex(i);
                _bloodArr->removeObject(_blood);
                this->removeChild(_blood, true);
            }
            iNum = iNum - _iDamage;
        }else{
            return;
        }
    }
}

#pragma mark - 游戏结束
void Joystick::endGame()
{
    this->unschedule(schedule_selector(Joystick::timeLabel));
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *youLose = CCSprite::create("youLose.png");
    youLose->setPosition(ccp(winSize.width/2, winSize.height+40));
    this->addChild(youLose,10);
    
    CCMoveBy *youLosewait = CCMoveBy::create(0.8, ccp(0, 0));
    CCMoveTo *youLoseMoveTo = CCMoveTo::create(0.5, ccp(winSize.width/2, winSize.height/2));
    CCFadeOut *youLosewenFadeOut = CCFadeOut::create(0.7);
    CCFiniteTimeAction *youLoseAction = CCSequence::create(youLosewait,youLoseMoveTo,youLosewenFadeOut,NULL);
    
    youLose->runAction(youLoseAction);
    
    this->schedule(schedule_selector(BiBiLayer::turnLoseScene), 2);
}

void Joystick::winGame()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Win_Time", nowTime);
    
    this->unschedule(schedule_selector(Joystick::timeLabel));
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *win_wenzi_1 = CCSprite::create("win_wenzi_1.png");
    win_wenzi_1->setPosition(ccp(winSize.width/2, winSize.height+40));
    this->addChild(win_wenzi_1,3);
    
    CCSprite *win_wenzi_2 = CCSprite::create("win_wenzi_2.png");
    win_wenzi_2->setPosition(ccp(winSize.width/2, winSize.height+40));
    this->addChild(win_wenzi_2,3);
    
    CCSprite *win_wenzi_3 = CCSprite::create("win_wenzi_3.png");
    win_wenzi_3->setPosition(ccp(winSize.width/2, winSize.height+40));
    this->addChild(win_wenzi_3,3);
    
    CCMoveBy *wait1 = CCMoveBy::create(1.9, ccp(0, 0));
    CCMoveBy *wait2 = CCMoveBy::create(2.7, ccp(0, 0));
    CCMoveBy *wait3 = CCMoveBy::create(3.4, ccp(0, 0));
    CCMoveTo *wenM1 = CCMoveTo::create(0.4, ccp(winSize.width/2, winSize.height/2));
    CCMoveTo *wenM2 = CCMoveTo::create(0.3, ccp(winSize.width/2, winSize.height/2));
    CCMoveTo *wenM3 = CCMoveTo::create(0.2, ccp(winSize.width/2, winSize.height/2));
    CCFadeOut *wenF1 = CCFadeOut::create(0.3);
    CCFadeOut *wenF2 = CCFadeOut::create(0.2);
    CCFadeOut *wenF3 = CCFadeOut::create(0.1);
    CCMoveBy *wait4 = CCMoveBy::create(0.4, ccp(0, 0));
    CCMoveBy *wait5 = CCMoveBy::create(0.8, ccp(0, 0));
    
    CCFiniteTimeAction *wenAction1 = CCSequence::create(wait1,wenM1,wait4,wenF1,NULL);
    CCFiniteTimeAction *wenAction2 = CCSequence::create(wait2,wenM2,wait4,wenF2,NULL);
    CCFiniteTimeAction *wenAction3 = CCSequence::create(wait3,wenM3,wait5,wenF3,NULL);
    
    win_wenzi_1->runAction(wenAction1);
    win_wenzi_2->runAction(wenAction2);
    win_wenzi_3->runAction(wenAction3);
    
    this->schedule(schedule_selector(BiBiLayer::turnWinScene), 4.5);
}

void Joystick::initSnow()
{

    CCParticleSystemQuad *m_emitter=new CCParticleSystemQuad();
    m_emitter->initWithTotalParticles(1000);//900个粒子对象
    //设置图片
    m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addImage("snow.png"));
    //设置发射粒子的持续时间-1表示一直发射，0没有意义，其他值表示持续时间
    m_emitter->setDuration(-1);
    //设置中心方向,这个店是相对发射点，x正方向为右，y正方向为上
    m_emitter->setGravity(CCPoint(0,-240));
    
    
    //设置角度，角度的变化率
    m_emitter->setAngle(90);
    m_emitter->setAngleVar(360);
    
    
    //设置径向加速度，径向加速度的变化率
    m_emitter->setRadialAccel(50);
    m_emitter->setRadialAccelVar(0);
    
    //设置粒子的切向加速度，切向加速度的变化率
    m_emitter->setTangentialAccel(30);
    m_emitter->setTangentialAccelVar(0);
    
    
    //设置粒子的位置，位置的变化率
    m_emitter->setPosition(CCPoint(400,500));
    m_emitter->setPosVar(CCPoint(400,0));
    
    //设置粒子声明，生命的变化率
    m_emitter->setLife(7);
    m_emitter->setLifeVar(2);
    
    
    //设置粒子开始的自旋转速度，开始自旋转速度的变化率
    m_emitter->setStartSpin(30);
    m_emitter->setStartSpinVar(60);
    
    //设置结束的时候的自旋转以及自旋转的变化率
    m_emitter->setEndSpin(60);
    m_emitter->setEndSpinVar(60);
    
    ccColor4F cc;
    cc.a=1.0f;
    cc.b=255.0f;
    cc.g=255.0f;
    cc.r=255.0f;
    ccColor4F cc2;
    cc2.a=0;
    cc2.b=0;
    cc2.g=0;
    cc2.r=0;
    //设置开始的时候的颜色以及颜色的变化率
    m_emitter->setStartColor(cc);
    m_emitter->setStartColorVar(cc2);
    
    //设置结束的时候的颜色以及颜色的变化率
    m_emitter->setEndColor(cc);
    m_emitter->setEndColorVar(cc2);
    
    //设置开始时候粒子的大小，以及大小的变化率
    m_emitter->setStartSize(15);
    m_emitter->setStartSizeVar(10);
    
    //设置粒子结束的时候的大小，以及大小的变化率
    m_emitter->setEndSize(20.0f);
    m_emitter->setEndSizeVar(15.0f);
    
    //设置每秒钟产生粒子的数目
    m_emitter->setEmissionRate(50);
    
    //设置到背景上
    addChild(m_emitter);
}

#pragma mark - 时间
void Joystick::timeLabel()
{
    CCString *time;
    if (nowTime<10) {
        time = CCString::createWithFormat("00%i",nowTime);
    }else if(nowTime<100){
        time = CCString::createWithFormat("0%i",nowTime);
    }else if(nowTime<1000){
        time = CCString::createWithFormat("%i",nowTime);
    }else{
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCSprite *timeOut = CCSprite::create("timeOut.png");
        timeOut->setPosition(ccp(winSize.width/2, winSize.height+40));
        this->addChild(timeOut,10);
        
        CCMoveBy *timeOutwait = CCMoveBy::create(0.3, ccp(0, 0));
        CCMoveTo *timeOutMoveTo = CCMoveTo::create(0.5, ccp(winSize.width/2, winSize.height/2));
        CCFadeOut *timeOutFadeOut = CCFadeOut::create(0.5);
        CCFiniteTimeAction *youLoseAction = CCSequence::create(timeOutwait,timeOutMoveTo,timeOutFadeOut,NULL);
        timeOut->runAction(youLoseAction);
        
        this->endGame();
        return;
    }
    timeLb->setString(time->getCString());
    nowTime++;
}

