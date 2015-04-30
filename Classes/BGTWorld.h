//
//  BGTWorld.h
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#ifndef __BGT__BGTWorld__
#define __BGT__BGTWorld__

#include "cocos2d.h"
#include "WaveManager.h"

class MessageDispatcher;
class BGTWall;
class Character;
class GameEntityManager;
class Weapon;
class Knife;
class Pistol;
#include <spine/spine-cocos2dx.h>
USING_NS_CC;
using namespace spine;

class GameScene;

class BGTWorld : public Node
{
private:
    int currentLevelIndex,currentWaveIndex;
    Sprite *gameBgSprite;
    Label *waveTip;
    Layer *uiLayer;
    LevelData *currentLevelData;
    GameScene *gameScene;
    Layer *bgLayer;
    Layer *monsterLayer;
    Layer *battlefieldLayer;
    Layer *weaponLayer;
    Vector<Weapon*> weapons;
    Weapon *currentWeapon;
    WaveManager *waveManager;
    Wave *currentWave;
    //road2 是wall的y
    float road0Y,road1Y,road2Y,road3Y,road4Y;
    Vector<Character*> monsterPool;
    float *roads;
    unsigned int waveEnemyNumLeftToBeOut;//这一波还剩多少怪要出击
    unsigned int totalKilledNum,waveKilledNum;
    float nextWaveOutTimeLeft;
    BGTWall *wall;
    Knife *knife;
    Pistol *pistol;
    
    MessageDispatcher *dispatcher;
    GameEntityManager *entityManager;
    
    Character* getIdleEnemyByTypeFromPoolForInit(int type);
    Character* getIdleEnemyByTypeFromPool(int type);
    //这一波过去的时间
    float timePast;
    bool showedNextWaveUI;
public:
    void reset();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithGameScene(GameScene *gs);
    BGTWorld();
    ~BGTWorld();
    // implement the "static create()" method manually
    void createWorld(int level);
    
    void update(float dt);
    
    void toggleWeapon();
    
    void wallDie();
    void showNextWaveUI();
    void resumeGame();
    void pauseGame();
    
    //当一个怪物死亡时，这个函数会被怪物对象调用
    void monsterDied(Character* monster);
    
    void nextWave();
    
    
    void startGame();
    void endGame(bool isWin);
    
    void shake( float d, float strength );
    
    Vector<Character*> getMonsters();
    
    BGTWall* getWall();
    
    void onEnter();
    void onEnterTransitionDidFinish();
    void onExit();
    void onExitTransitionDidStart();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
};

#endif /* defined(__BGT__BGTWorld__) */
