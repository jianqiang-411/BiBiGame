//
//  BiBiLayer.h
//  BiBiGame
//
//  Created by Zhusy on 13-6-24.
//
//

#ifndef __BiBiGame__BiBiLayer__
#define __BiBiGame__BiBiLayer__

#include <iostream>
#include "Hero.h"
#include "Boss.h"
#include "cocos2d.h"
#include "SimpleDPad.h"
#include "FireBTN.h"
#include "Joystick.h"
#include "BiBiAction.h"
//#include "BiBiScene.h"
using namespace cocos2d;

class BiBiLayer:public CCLayer, public SimpleDPadDelegate,public FireBTNDelegate
{
public:
    CREATE_FUNC(BiBiLayer);
//    BiBiAction *_bibiAction;
    
    BiBiLayer();
    ~BiBiLayer();
    //背景添加
    bool init();
    void initTileMap();
    CCTMXTiledMap *_tileMap;
    
    //添加图片plist文件与ccz文件
    CCSpriteBatchNode *_actors;
    
    //英雄添加
    Hero *_hero;
    
//    Boss *_bBoss;
//    Monster *_monster;
    void initHero();
    void initProjectile();
    
    //触碰发子弹
//    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    
    //虚拟键盘
    virtual void didChangeDirectionTo(SimpleDPad *simpleDPad, cocos2d::CCPoint direction);
    virtual void isHoldingDirection(SimpleDPad *simpleDPad, cocos2d::CCPoint direction);
    virtual void simpleDPadTouchEnded(SimpleDPad *simpleDPad);
    
    virtual void PressMetoFire(FireBTN *simpleDPad);
    
    CC_SYNTHESIZE(Joystick*, _joyS, joyS);
    //移动
    void update(float dt);
    void updatePositions();
    void win_OR_lose();
    //地图跟着英雄位置变化
    void setViewpointCenter(CCPoint position);
    //怪物
    CC_SYNTHESIZE_RETAIN(CCArray*,_monsters, monsters);
    CC_SYNTHESIZE_RETAIN(CCArray*, _fireGirlArr, fireGirlArr);
    CC_SYNTHESIZE_RETAIN(CCArray*, _boss, boss);
    CC_SYNTHESIZE_RETAIN(CCArray*, _sBossArr, sBossArr);
    //召唤怪物数组
    CC_SYNTHESIZE_RETAIN(CCArray*, _outMonsterArr, outMonsterArr)
    //史莱姆
    CC_SYNTHESIZE_RETAIN(CCArray*, _SLM_1_Arr, SLM_1_Arr);
    CC_SYNTHESIZE_RETAIN(CCArray*, _SLM_2_Arr, SLM_2_Arr);
    CC_SYNTHESIZE_RETAIN(CCArray*, _SLM_3_Arr, SLM_3_Arr);
    //最终BOSS
    CC_SYNTHESIZE_RETAIN(CCArray*, _tBossArr, tBossArr);
    
    void initMonsters();
    void initFireGirl();
    void initBosses();
    void initBigSLM();
    void initMiddleSLM();
    void initSmallSLM();
    
    //添加z轴
    void reorderActors();
    
    //攻击相关,缓冲对象
    CCSpriteFrameCache* cache;
    CCArray *FireArr;
    int numFire;
    
    //怪物ai
    void updateMonsters(float dt);
    void updateOutMonsters(float dt);
    void updateFireGirl(float dt);
    void updateBigSLM(float dt);
    void updateMiddleSLM(float dt);
    void updateSmallSLM(float dt);
    void updateBoss(float dt);
    void updateSBoss(float dt);
    void updateTBoss(float dt);
    
    //fireGirl子弹
    CCArray *fireGirlFireArr;
    int numFireGirlFire;
    
    //BOSS子弹
    CCArray *BossFireArr;
    int numBossFire;
    
    //攻击伤血
    void updateHeroProjectile(float dt);
    void updateBossProjectile(float dt);
    void updateFireGirlProjectile(float dt);
//    CCArray *_arrMonster;
//    CCArray *_arrProjectile;
//    void spriteMoveFinished(CCNode *sender);
    int _monstersDestroyed;
    
    void turnWinScene();
    void turnLoseScene();
    void restartGame(CCObject* pSender);
    void backMeun(CCObject* pSender);
    
    void BossFire();
    void GirlFire();
    bool collisionWithCircle(CCPoint circlePoint, float radius, CCPoint circlePointTwo, float radiusTwo);
    
    //胜利/失败，条件判断中间变量
    int tempBoss = 0;
    int tempSBoss = 0;
    int tempTBoss = 0;
    int ifWin = 0;
    int ifLose = 0;
    
    //二号boss召唤一号boss中间变量
    int sBossFindBoss = 0;
    
    //判断2号boss召唤怪物最多召唤100个
    int outMonsterNum = 0;
    int outSmallSLMNum = 0;
    
};

#endif /* defined(__BiBiGame__BiBiLayer__) */
