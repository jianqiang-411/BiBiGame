//
//  MeunScence.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-6-28.
//
//

#include "MeunScence.h"
#include "ChooseRobet.h"
#include "HighScore.h"

bool MeunScence::init()
{
    bool bRet = false;
    do {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite *background = CCSprite::create("star_2.png");
        background->setPosition(ccp(-winSize.width/2, winSize.height/2));
        this->addChild(background,-5);
        CCMoveTo *movett = CCMoveTo::create(0, ccp(winSize.width/2, winSize.height/2));
        CCFadeOut *fadeout1 = CCFadeOut::create(0);
        CCFadeIn *fadein = CCFadeIn::create(3);
        CCFiniteTimeAction *backaction = CCSequence::create(fadeout1,movett,fadein,NULL);
        background->runAction(backaction);
        
        CCSprite *star = CCSprite::create("star_3.png");
        star->setPosition(ccp(-winSize.width/2, winSize.height/2));
        this->addChild(star,-3);
        CCFadeOut *starFadeOut = CCFadeOut::create(0);
        CCMoveTo *starMoveTo = CCMoveTo::create(0, ccp(winSize.width/2, winSize.height/2-300));
        CCFadeIn *starFadeIn = CCFadeIn::create(3);
        CCRotateBy *starRotate = CCRotateBy::create(30, 360);
        CCFiniteTimeAction *starAction = CCSequence::create(starFadeOut,starMoveTo,starFadeIn,NULL);
        CCFiniteTimeAction *starAction2 = CCRepeatForever::create(starRotate);
        star->runAction(starAction);
        star->runAction(starAction2);
        
        CCSprite *start = CCSprite::create("start.png");
        start->setPosition(ccp(-winSize.width/2, winSize.height/2));
        this->addChild(start,-2);
        CCFadeOut *startFadeOut = CCFadeOut::create(0);
        CCMoveTo *startMoveTo = CCMoveTo::create(0, ccp(winSize.width/2+180, winSize.height/2-100));
        CCFadeIn *startFadeIn = CCFadeIn::create(2);
//        CCRotateBy *startRotate = CCRotateBy::create(5, -360);
        CCFiniteTimeAction *startAction_1 = CCSequence::create(startFadeOut,startMoveTo,startFadeIn,NULL);
//        CCFiniteTimeAction *startAction_2 = CCRepeatForever::create(startRotate);
        start->runAction(startAction_1);
//        start->runAction(startAction_2);
        
        CCSprite *highScore = CCSprite::create("PaiHB.png");
        highScore->setPosition(ccp(-winSize.width/2, winSize.height/2));
        this->addChild(highScore,-2);
        CCFadeOut *highScoreFadeOut = CCFadeOut::create(0);
        CCMoveTo *highScoreMoveTo = CCMoveTo::create(0, ccp(winSize.width/2-200, winSize.height/2+130));
        CCFadeIn *highScoreFadeIn = CCFadeIn::create(2);
        CCFiniteTimeAction *highScoreAction_1 = CCSequence::create(highScoreFadeOut,highScoreMoveTo,highScoreFadeIn,NULL);
        highScore->runAction(highScoreAction_1);

        
        CCMenuItemImage *highScoreImg = CCMenuItemImage::create("null_3.png", "null_3.png", this, menu_selector(MeunScence::highScore));
        highScoreImg->setPosition( ccp(winSize.width/2-200, winSize.height/2+130) );
        
        CCMenuItemImage *startImg = CCMenuItemImage::create("null_2.png", "null_2.png", this, menu_selector(MeunScence::changeScence));
        startImg->setPosition( ccp(winSize.width/2+180, winSize.height/2-100) );
        
        SMenu = CCMenu::create(startImg,highScoreImg, NULL);
        SMenu->setPosition( CCPointZero );
        this->addChild(SMenu, 2);
        
        CCSprite *UFO = CCSprite::create("UFO.png");
        UFO->setPosition(ccp(-winSize.width/2, winSize.height/2));
        this->addChild(UFO,-1);
        CCFadeOut *UFOFadeOut = CCFadeOut::create(0);
        CCMoveTo *UFOMoveTo = CCMoveTo::create(0, ccp(winSize.width/2-120, winSize.height/2+80));
        CCMoveBy *UFOMoveBy_1 = CCMoveBy::create(3, ccp(-80, -30));
        CCMoveBy *UFOMoveBy_2 = CCMoveBy::create(2, ccp(50, -100));
        CCMoveBy *UFOMoveBy_3 = CCMoveBy::create(1, ccp(340, 125));//(430,235)
        CCFadeIn *UFOFadeIn = CCFadeIn::create(3);
        CCActionInterval *scaleTo_1= CCScaleTo::create(0, 0.01);
        CCActionInterval *scaleTo_2= CCScaleTo::create(2, 1);
        CCActionInterval *scaleTo_3= CCScaleTo::create(3, 0.3);
        CCActionInterval *scaleTo_4= CCScaleTo::create(1, 0.6);
        CCRotateBy *UFORotate_1 = CCRotateBy::create(3, 30);
        CCRotateBy *UFORotate_2 = CCRotateBy::create(2, -40);
        CCRotateBy *UFORotate_3 = CCRotateBy::create(1, -30);
        CCRotateBy *UFORotate_4 = CCRotateBy::create(0.1, 70);
        CCRotateBy *UFORotate_5 = CCRotateBy::create(0.1, -60);
        CCRotateBy *UFORotate_6 = CCRotateBy::create(0.1, 60);
        CCRotateBy *UFORotate_7 = CCRotateBy::create(0.1, -60);
        CCRotateBy *UFORotate_8 = CCRotateBy::create(0.1, 60);
        CCRotateBy *UFORotate_9 = CCRotateBy::create(0.1, -60);
        CCRotateBy *wait = CCRotateBy::create(1, 0);
        CCFiniteTimeAction *UFOAction_1 = CCSequence::create(UFOFadeOut,scaleTo_1,UFOMoveTo,NULL);
        CCFiniteTimeAction *UFOAction_2 = CCSpawn::create(UFOFadeIn,UFORotate_1,UFOMoveBy_1,scaleTo_3,NULL);
        CCFiniteTimeAction *UFOAction_3 = CCSpawn::create(UFORotate_2,UFOMoveBy_2,scaleTo_2,NULL);
        CCFiniteTimeAction *UFOAction_4 = CCSpawn::create(UFORotate_3,UFOMoveBy_3,scaleTo_4,NULL);
        CCFiniteTimeAction *UFOAction_5 = CCSequence::create(wait,UFORotate_4,UFORotate_5,UFORotate_6,UFORotate_7,UFORotate_8,UFORotate_9,NULL);
        CCFiniteTimeAction *UFOAction = CCSequence::create(UFOAction_1,UFOAction_2,UFOAction_3,UFOAction_4,UFOAction_5,NULL);
        UFO->runAction(UFOAction);
        
        //schedule使schedule_selector每隔“多少”秒执行一次
        this->schedule(schedule_selector(MeunScence::play), 6.6);
        bRet = true;
    } while (0);
    return bRet;
}

void MeunScence::play()
{
    //unschedule停止schedule_selector的间隔执行
    this->unschedule(schedule_selector( MeunScence::play));
    CCSprite *play = CCSprite::create("here.png");
    play->setOpacity(200);
    play->setPosition(ccp(-200, 280));
    this->addChild(play);
    CCFadeOut *playFadeOut = CCFadeOut::create(0);
    CCMoveTo *playMoveTo = CCMoveTo::create(0,ccp(390, 280));
    CCFadeIn *playFadeIn = CCFadeIn::create(0.3);
    CCFiniteTimeAction *playAction = CCSequence::create(playFadeOut,playMoveTo,playFadeIn,NULL);
    play->runAction(playAction);
    
    CCMenuItemImage *playImg = CCMenuItemImage::create("null.png", "null.png", this, menu_selector(MeunScence::logo));
    playImg->setPosition( ccp(430, 235) );
    pMenu = CCMenu::create(playImg, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 2);
 
    
}

void MeunScence::logo()
{
    //是暂停按钮点击一次后不能再次按
    pMenu->setEnabled(false);
    SMenu->setEnabled(false);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    logoP = CCSprite::create("logo.png");
    logoP->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(logoP,5);
    
    CCMenuItemImage *xxImg = CCMenuItemImage::create("xx.png", "xx.png", this, menu_selector(MeunScence::xxlogo));
    xxImg->setPosition( ccp(winSize.width/2+150, winSize.height/2+95));
    xMenu = CCMenu::create(xxImg, NULL);
    xMenu->setPosition( CCPointZero );
    this->addChild(xMenu, 6);
    
}

void MeunScence::xxlogo()
{
    this->removeChild(xMenu, true);
    this->removeChild(logoP, true);
    pMenu->setEnabled(true);
    SMenu->setEnabled(true);
}
//void MeunScence::delay()
//{
//      this->addChild(pMenu, 2);
//}

void MeunScence::changeScence()
{
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *chooserobet = ChooseRobet::create();
    pDirector->replaceScene(chooserobet);
}

void MeunScence::highScore()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *highScore = HighScore::create();
    pDirector->replaceScene(highScore);
}