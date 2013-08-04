//
//  WinScene.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-7-5.
//
//

#include "WinScene.h"
#include "BiBiLayer.h"
#include "Joystick.h"
#include "MeunScence.h"
#include "BiBiScene.h"

bool WinScene::init()
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
        
        CCSprite *winBackground = CCSprite::create("win.png");
        winBackground->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(winBackground,0);
        
        CCMenuItemImage *restartBtn = CCMenuItemImage::create("winBtn_null.png", "winBtn_null.png", this, menu_selector(BiBiLayer::restartGame));
        restartBtn->setPosition(ccp(winSize.width/2-3, winSize.height/2-125));
        
        CCMenuItemImage *menuBtn = CCMenuItemImage::create("winBtn_null.png", "winBtn_null.png", this, menu_selector(Joystick::menu));
        menuBtn->setPosition(ccp(winSize.width/2-114, winSize.height/2-125));
        
        CCMenuItemImage *nextBtn = CCMenuItemImage::create("winBtn_null.png", "winBtn_null.png", this, menu_selector(WinScene::GameLevel));
        nextBtn->setPosition(ccp(winSize.width/2+110, winSize.height/2-125));
        
        CCMenu *rMenu = CCMenu::create(restartBtn,menuBtn,nextBtn,NULL);
        rMenu->setPosition(CCPointZero);
        this->addChild(rMenu,1);
        
        tiSK = CCSprite::create("TiSK.png");
        tiSK->setPosition(ccp(-winSize.width/2+110, winSize.height/2-125));
        tiSK->setVisible(false);
        this->addChild(tiSK,3);
        
        //胜利显示通关时间
        CCLabelTTF *timeWZ = CCLabelTTF::create("通关时间", "Verdana", 20);
        timeWZ->setPosition(ccp(winSize.width/2-50, 220));
        timeWZ->setColor(ccc3(0, 0, 0));
        this->addChild(timeWZ);
        
        CCLabelTTF *timeMH = CCLabelTTF::create(":", "Verdana-Bold", 20);
        timeMH->setPosition(ccp(winSize.width/2, 220));
        timeMH->setColor(ccc3(0, 0, 0));
        this->addChild(timeMH);
        
        int Win_Time = CCUserDefault::sharedUserDefault()->getIntegerForKey("Win_Time");
        int Level = CCUserDefault::sharedUserDefault()->getIntegerForKey("Level");
        if (Level == 1) {
            int MARKTIME_1 = CCUserDefault::sharedUserDefault()->getIntegerForKey("MARKTIME_1");
            if (MARKTIME_1 >Win_Time) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("MARKTIME_1", Win_Time);
                CCUserDefault::sharedUserDefault()->flush();
                CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
            }
        }else if(Level == 2){
            int MARKTIME_2 = CCUserDefault::sharedUserDefault()->getIntegerForKey("MARKTIME_2");
            if (MARKTIME_2 >Win_Time) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("MARKTIME_2", Win_Time);
                CCUserDefault::sharedUserDefault()->flush();
                CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
            }
        }else if(Level == 3){
            int MARKTIME_3 = CCUserDefault::sharedUserDefault()->getIntegerForKey("MARKTIME_3");
            if (MARKTIME_3 >Win_Time) {
                CCUserDefault::sharedUserDefault()->setIntegerForKey("MARKTIME_3", Win_Time);
                CCUserDefault::sharedUserDefault()->flush();
                CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
            }
        }
        
        
        CCString *winTime = CCString::createWithFormat("%d",Win_Time);
        CCLabelTTF *timeSJ = CCLabelTTF::create(winTime->getCString(), "Verdana-Bold", 30);
        timeSJ->setPosition(ccp(winSize.width/2+50, 220));
        timeSJ->setColor(ccc3(255, 0, 0));
        this->addChild(timeSJ);
        
        CCLabelTTF *timeM = CCLabelTTF::create("秒", "Verdana", 20);
        timeM->setPosition(ccp(winSize.width/2+100, 220));
        timeM->setColor(ccc3(0, 0, 0));
        this->addChild(timeM);
        
        
        bRet = true;
    } while (0);
    return bRet;
}

void WinScene::GameLevel()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int whichlevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("Level");
    whichlevel = whichlevel + 1;
    if (whichlevel > 3) {
        tiSK->setVisible(true);
        CCFadeIn *tiSKFadeIn = CCFadeIn::create(0);
        CCMoveTo *tiSKMoveTo = CCMoveTo::create(0, ccp(winSize.width/2+110, winSize.height/2-60));
        CCMoveBy *wait = CCMoveBy::create(0.5, ccp(0, 0));
        CCFadeOut *tiSKFadeOut = CCFadeOut::create(1);
        CCFiniteTimeAction *tiSKAction = CCSequence::create(tiSKFadeIn,tiSKMoveTo,wait,tiSKFadeOut,NULL);
        tiSK->stopAllActions();
        tiSK->runAction(tiSKAction);
    }else{
        CCUserDefault::sharedUserDefault()->setIntegerForKey("Level", whichlevel);
        CCDirector::sharedDirector()->replaceScene(BiBiScene::create());
    }
    
    
}
