//
//  ChooseMap.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-7-11.
//
//

#include "ChooseMap.h"
#include "BiBiScene.h"

bool ChooseMap::init()
{
    bool bRet = false;
    do {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCMenuItemImage *choose1 = CCMenuItemImage::create("choose_1_map.png", "choose_1_map.png", this, menu_selector(ChooseMap::choose_1_Map));
        choose1->setPosition(ccp(winSize.width/2, winSize.height/2+106));
        CCMenuItemImage *choose2 = CCMenuItemImage::create("choose_2_map.png", "choose_2_map.png", this, menu_selector(ChooseMap::choose_2_Map));
        choose2->setPosition(ccp(winSize.width/2, winSize.height/2+2));
        CCMenuItemImage *choose3 = CCMenuItemImage::create("choose_3_map.png", "choose_3_map.png", this, menu_selector(ChooseMap::choose_3_Map));
        choose3->setPosition(ccp(winSize.width/2, winSize.height/2-102));
        
        CCMenu *pMenu = CCMenu::create(choose1,choose2,choose3,NULL);
        pMenu->setPosition(CCPointZero);
        this->addChild(pMenu,0);
        
        bRet = true;
    } while (0);
    return bRet;
}

void ChooseMap::choose_1_Map()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Level", 1);
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *bibiScene = BiBiScene::create();
    pDirector->replaceScene(bibiScene);
}

void ChooseMap::choose_2_Map()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Level", 2);
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *bibiScene = BiBiScene::create();
    pDirector->replaceScene(bibiScene);
}

void ChooseMap::choose_3_Map()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Level", 3);
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *bibiScene = BiBiScene::create();
    pDirector->replaceScene(bibiScene);
}