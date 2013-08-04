//
//  ChooseRobet.cpp
//  BiBiGame
//
//  Created by 蛋儿宝A+ on 13-6-30.
//
//

#include "ChooseRobet.h"
#include "ChooseMap.h"

bool ChooseRobet::init()
{
    bool bRet = false;
    do {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCMenuItemImage *choose1 = CCMenuItemImage::create("choose_1.png", "choose_1.png", this, menu_selector(ChooseRobet::choose_1));
        choose1->setPosition(ccp(winSize.width/2-100, winSize.height/2));
        CCMenuItemImage *choose2 = CCMenuItemImage::create("choose_2.png", "choose_2.png", this, menu_selector(ChooseRobet::choose_2));
        choose2->setPosition(ccp(winSize.width/2+100, winSize.height/2));
        CCMenu *pMenu = CCMenu::create(choose1,choose2,NULL);
        pMenu->setPosition(CCPointZero);
        this->addChild(pMenu,0);

        
        bRet=true;
    } while (0);
    return bRet;
}

void ChooseRobet::choose_1()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("num", 1);
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *chooseMap = ChooseMap::create();
    pDirector->replaceScene(chooseMap);
}


void ChooseRobet::choose_2()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("num", 2);
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *chooseMap = ChooseMap::create();
    pDirector->replaceScene(chooseMap);
}

