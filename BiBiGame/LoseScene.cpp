//
//  LoseScene.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-7-5.
//
//

#include "LoseScene.h"
#include "BiBiLayer.h"
#include "Joystick.h"
#include "MeunScence.h"
#include "BiBiScene.h"

bool LoseScene::init()
{
    bool bRet = false;
    do {
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite *winZ = CCSprite::create("zhuan.png");
        winZ->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(winZ,0);
        CCRotateBy *winZRotate = CCRotateBy::create(10, 360);
        CCFiniteTimeAction *winZAction = CCRepeatForever::create(winZRotate);
        winZ->runAction(winZAction);
        
        CCSprite *loseBackground = CCSprite::create("lose.png");
        loseBackground->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(loseBackground,0);
        CCFiniteTimeAction *loseBackAction = CCSequence::create(CCFadeOut::create(0),CCMoveBy::create(0.9, ccp(0, 0)),CCFadeIn::create(1),NULL);
        loseBackground->runAction(loseBackAction);
        
        CCSprite *loseImg = CCSprite::create("GameOver.png");
        loseImg->setPosition(ccp(-winSize.width/2-100, winSize.height/2+100));
        this->addChild(loseImg,1);
        CCFiniteTimeAction *loseImgAction = CCSequence::create(CCFadeOut::create(0),CCScaleTo::create(0, 5),CCRotateBy::create(0, -15),CCMoveTo::create(0, ccp(winSize.width/2-100, winSize.height/2+100)),CCMoveBy::create(3, ccp(0, 0)),CCFadeIn::create(0),CCScaleTo::create(0.5, 1),NULL);
        loseImg->runAction(loseImgAction);
        
        CCSprite *winBackground = CCSprite::create("win.png");
        winBackground->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(winBackground,0);
        CCFadeOut *winBackFadeOut = CCFadeOut::create(0.5);
        CCFiniteTimeAction *winBackAction = CCSequence::create(CCMoveBy::create(0.5, ccp(0, 0)),winBackFadeOut,NULL);
        winBackground->runAction(winBackAction);
        
        CCMenuItemImage *restartBtn = CCMenuItemImage::create("winBtn_null.png", "winBtn_null.png", this, menu_selector(BiBiLayer::restartGame));
        restartBtn->setPosition(ccp(winSize.width/2-3, winSize.height/2-125));
        
        CCMenuItemImage *menuBtn = CCMenuItemImage::create("winBtn_null.png", "winBtn_null.png", this, menu_selector(Joystick::menu));
        menuBtn->setPosition(ccp(winSize.width/2-114, winSize.height/2-125));
        
        CCMenuItemImage *nextBtn = CCMenuItemImage::create("winBtn_null.png", "winBtn_null.png", this, menu_selector(LoseScene::youLose));
        nextBtn->setPosition(ccp(winSize.width/2+110, winSize.height/2-125));
        
        CCMenu *rMenu = CCMenu::create(restartBtn,menuBtn,nextBtn,NULL);
        rMenu->setPosition(CCPointZero);
        this->addChild(rMenu,1);
        
        loseTiSK = CCSprite::create("no.png");
        loseTiSK->setPosition(ccp(winSize.width/2+110, winSize.height/2-125));
        loseTiSK->setVisible(false);
        this->addChild(loseTiSK,3);
        
        bRet = true;
    } while (0);
    return bRet;
}

void LoseScene::youLose()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    loseTiSK->setVisible(true);
    CCFadeIn *loseTiSKFadeIn = CCFadeIn::create(0);
    CCFadeOut *loseTiSKFadeOut = CCFadeOut::create(0.5);
    CCFiniteTimeAction *loseTiSKAction = CCSequence::create(loseTiSKFadeIn,loseTiSKFadeOut,NULL);
    loseTiSK->stopAllActions();
    loseTiSK->runAction(loseTiSKAction);
}
