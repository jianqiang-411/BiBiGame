//
//  BiBiGameAppDelegate.cpp
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"
#include "cocos2d.h"
//#include "BiBiScene.h"
//#include "MeunScence.h"
#include "CartoonScene.h"
#define CCUD CCUserDefault::sharedUserDefault()

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    // pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCUD->setIntegerForKey("ifGirl", 0);
    CCUD->setIntegerForKey("ifBoss", 0);
    CCUD->setIntegerForKey("num", 0);
    CCUD->setIntegerForKey("girlFX", 0);
    CCUD->setIntegerForKey("bossFX", 0);
    CCUD->setIntegerForKey("Win_Time", 0);
    CCUD->setIntegerForKey("Level", 0);
    
    bool ifFiretBegin = CCUD->getBoolForKey("ifFiretBegin");
    if (ifFiretBegin) {
        
        
//        CCUD->setBoolForKey("ifFiretBegin", false);
//        CCUserDefault::sharedUserDefault()->flush();
//        CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
    }else{
        CCUD->setBoolForKey("ifFiretBegin", true);
        CCUD->setIntegerForKey("MARKTIME_1", 999);
        CCUD->setIntegerForKey("MARKTIME_2", 999);
        CCUD->setIntegerForKey("MARKTIME_3", 999);
        CCUserDefault::sharedUserDefault()->flush();
        CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
    }
    
    int MARKTIME_1 = CCUD->getIntegerForKey("MARKTIME_1");
    int MARKTIME_2 = CCUD->getIntegerForKey("MARKTIME_2");
    int MARKTIME_3 = CCUD->getIntegerForKey("MARKTIME_3");
    if (MARKTIME_1 == 0) {
        CCUD->setIntegerForKey("MARKTIME_1", 999);
        CCUserDefault::sharedUserDefault()->flush();
        CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
    }
    if (MARKTIME_2 == 0) {
        CCUD->setIntegerForKey("MARKTIME_2", 999);
        CCUserDefault::sharedUserDefault()->flush();
        CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
    }
    if (MARKTIME_3 == 0) {
        CCUD->setIntegerForKey("MARKTIME_3", 999);
        CCUserDefault::sharedUserDefault()->flush();
        CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
    }
    

    // create a scene. it's an autorelease object
//    CCScene *pScene = BiBiScene::create();
    CCScene *cartoonScene = CartoonScene::create();
    // run
//    pDirector->runWithScene(pScene);
    pDirector->runWithScene(cartoonScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
