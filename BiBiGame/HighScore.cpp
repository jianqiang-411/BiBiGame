//
//  HighScore.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-7-10.
//
//

#include "HighScore.h"
#include "MeunScence.h"

#define WINSIZE CCDirector::sharedDirector()->getWinSize()
bool HighScore::init()
{
    bool bRet = false;
    do {        
        CCSprite *winZ = CCSprite::create("zhuan.png");
        winZ->setPosition(ccp(WINSIZE.width/2, WINSIZE.height/2));
        this->addChild(winZ,0);
        CCRotateBy *winZRotate = CCRotateBy::create(10, 360);
        CCFiniteTimeAction *winZAction = CCRepeatForever::create(winZRotate);
        winZ->runAction(winZAction);
        
        CCSprite *backOutK = CCSprite::create("backOutK.png");
        backOutK->setPosition(ccp(WINSIZE.width/2, WINSIZE.height/2));
        this->addChild(backOutK);
        
        CCMenuItemImage *backMenu = CCMenuItemImage::create("back.png", "back.png", this, menu_selector(HighScore::back));
        backMenu->setPosition( ccp(WINSIZE.width/2-210, WINSIZE.height/2+130) );
        
        CCMenu *SMenu = CCMenu::create(backMenu,NULL);
        SMenu->setPosition( CCPointZero );
        this->addChild(SMenu, 2);
        
        //通关时间记录
        CCLabelTTF *WZ_PHB = CCLabelTTF::create("排行榜", "Verdana-Bold", 50);
        WZ_PHB->setPosition(ccp(WINSIZE.width/2, 290));
        WZ_PHB->setColor(ccc3(255, 0, 0));
        this->addChild(WZ_PHB,2);
        
        this->initHighScore_1();
        this->initHighScore_2();
        this->initHighScore_3();
        
        bRet = true;
    } while (0);
    return bRet;
}

void HighScore::back()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *menuScene = MeunScence::create();
    pDirector->replaceScene(menuScene);
}

void HighScore::initHighScore_1()
{
    CCSprite *backInK = CCSprite::create("backInK.png");
    backInK->setPosition(ccp(WINSIZE.width/2-119, 45));
    this->addChild(backInK,0);
    
    CCSprite *Level_1_map = CCSprite::create("Level_1_map.png");
    Level_1_map->setPosition(ccp(WINSIZE.width/2-119, WINSIZE.height/2+23));
    this->addChild(Level_1_map,0);
    
    int MARKTIME_1 = CCUserDefault::sharedUserDefault()->getIntegerForKey("MARKTIME_1");
    CCLOG("-----%d",MARKTIME_1);
    CCString *MARKTIME = CCString::createWithFormat("%d",MARKTIME_1);
    CCLabelTTF *MARKTIME_SJ = CCLabelTTF::create(MARKTIME->getCString(), "Verdana-Bold", 30);
    MARKTIME_SJ->setPosition(ccp(WINSIZE.width/2-135, 45));
    MARKTIME_SJ->setColor(ccc3(255, 255, 255));
    this->addChild(MARKTIME_SJ);
    
    CCLabelTTF *MARKTIME_M = CCLabelTTF::create("S", "Verdana-Bold", 20);
    MARKTIME_M->setPosition(ccp(WINSIZE.width/2-80, 45));
    MARKTIME_M->setColor(ccc3(255, 255, 255));
    this->addChild(MARKTIME_M);
}

void HighScore::initHighScore_2()
{
    CCSprite *backInK = CCSprite::create("backInK.png");
    backInK->setPosition(ccp(WINSIZE.width/2, 45));
    this->addChild(backInK,0);
    
    CCSprite *Level_2_map = CCSprite::create("Level_2_map.png");
    Level_2_map->setPosition(ccp(WINSIZE.width/2, WINSIZE.height/2+23));
    this->addChild(Level_2_map,0);
    
    int MARKTIME_2 = CCUserDefault::sharedUserDefault()->getIntegerForKey("MARKTIME_2");
    
    CCString *MARKTIME = CCString::createWithFormat("%d",MARKTIME_2);
    CCLabelTTF *MARKTIME_SJ = CCLabelTTF::create(MARKTIME->getCString(), "Verdana-Bold", 30);
    MARKTIME_SJ->setPosition(ccp(WINSIZE.width/2-15, 45));
    MARKTIME_SJ->setColor(ccc3(255, 255, 255));
    this->addChild(MARKTIME_SJ);
    
    CCLabelTTF *MARKTIME_M = CCLabelTTF::create("S", "Verdana-Bold", 20);
    MARKTIME_M->setPosition(ccp(WINSIZE.width/2+40, 45));
    MARKTIME_M->setColor(ccc3(255, 255, 255));
    this->addChild(MARKTIME_M);
}

void HighScore::initHighScore_3()
{
    CCSprite *backInK = CCSprite::create("backInK.png");
    backInK->setPosition(ccp(WINSIZE.width/2+119, 45));
    this->addChild(backInK,0);
    
    CCSprite *Level_1_map = CCSprite::create("Level_3_map.png");
    Level_1_map->setPosition(ccp(WINSIZE.width/2+119, WINSIZE.height/2+23));
    this->addChild(Level_1_map,0);
    
    int MARKTIME_3 = CCUserDefault::sharedUserDefault()->getIntegerForKey("MARKTIME_3");
    
    CCString *MARKTIME = CCString::createWithFormat("%d",MARKTIME_3);
    CCLabelTTF *MARKTIME_SJ = CCLabelTTF::create(MARKTIME->getCString(), "Verdana-Bold", 30);
    MARKTIME_SJ->setPosition(ccp(WINSIZE.width/2+105, 45));
    MARKTIME_SJ->setColor(ccc3(255, 255, 255));
    this->addChild(MARKTIME_SJ);
    
    CCLabelTTF *MARKTIME_M = CCLabelTTF::create("S", "Verdana-Bold", 20);
    MARKTIME_M->setPosition(ccp(WINSIZE.width/2+160, 45));
    MARKTIME_M->setColor(ccc3(255, 255, 255));
    this->addChild(MARKTIME_M);
}
