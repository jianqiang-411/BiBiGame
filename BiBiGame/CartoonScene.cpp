//
//  CartoonScene.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-7-1.
//
//

#include "CartoonScene.h"
#include "MeunScence.h"

bool CartoonScene::init()
{
    bool bRet = false;
    do {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite *backgroundImg = CCSprite::create("meun_background_1.png");
        backgroundImg->setPosition(ccp(winSize.width/2,winSize.height/2));
        this->addChild(backgroundImg,-1);
        
        CCMenuItemImage *skip = CCMenuItemImage::create("SkipToStart.png","SkipToStart.png",this,menu_selector(CartoonScene::changeScence) );
        skip->setPosition( ccp(winSize.width/2, 20) );
        // create menu, it's an autorelease object
        pMenu = CCMenu::create(skip, NULL);
        pMenu->setPosition( CCPointZero );
        this->addChild(pMenu, 1);
        //        sMenu->retain();
//        this->schedule(schedule_selector(CartoonScene::del), 10);
        
        CCSprite *robet1 = CCSprite::create("meun_Robet.png");
        robet1->setPosition(ccp(-185, 160));
        this->addChild(robet1,0);
        CCMoveTo *m1 = CCMoveTo::create(1, ccp(200, 160));
        CCMoveTo *m2 = CCMoveTo::create(2, ccp(175, 160));
        CCMoveTo *m3 = CCMoveTo::create(1, ccp(700, 160));
        CCFiniteTimeAction *action1 = CCSequence::create(m1,m2,m3,NULL);
        robet1->runAction(action1);
        
        CCSprite *robet2 = CCSprite::create("meun_Gold.png");
        robet2->setPosition(ccp(630, 160));
        this->addChild(robet2,0);
        CCMoveBy *wait1 = CCMoveBy::create(4.5, ccp(0, 0));
        CCMoveTo *m4 = CCMoveTo::create(1, ccp(300, 160));
        CCMoveTo *m5 = CCMoveTo::create(2, ccp(330, 160));
        CCMoveTo *m6 = CCMoveTo::create(1, ccp(-150, 160));
        CCFiniteTimeAction *action2 = CCSequence::create(wait1,m4,m5,m6,NULL);
        robet2->runAction(action2);
        
        CCMoveBy *wait3 = CCMoveBy::create(9, ccp(0, 0));
        CCFadeOut *fadeout = CCFadeOut::create(3);
        //        CCMoveTo *mt1 = CCMoveTo::create(0.1, ccp(5, 0));
        //        CCMoveTo *mt2 = CCMoveTo::create(0.2, ccp(-10, 0));
        CCFiniteTimeAction *action3 = CCSequence::create(wait3,fadeout,NULL);
        backgroundImg->runAction(action3);
        
        this->schedule(schedule_selector(CartoonScene::changeScence), 12);
        
        
        bRet = true;
    } while (0);
    return bRet;
}

void CartoonScene::changeScence()
{
    this->unschedule(schedule_selector( CartoonScene::changeScence));
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    pDirector->setDisplayStats(true);
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCScene *meunscene = MeunScence::create();
    pDirector->replaceScene(meunscene);
}
