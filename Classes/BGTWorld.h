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
    unsigned int currentLevel;
    GameScene *gameScene;
    Layer *bgLayer;
    Layer *battlefieldLayer;
    Layer *weaponLayer;
    Vector<Weapon*> weapons;
    Weapon *currentWeapon;
    //road2 是wall的y
    float road0Y,road1Y,road2Y,road3Y,road4Y;
    Vector<Character*> monsterPool;
    float *roads;
    BGTWall *wall;
    Knife *knife;
    Pistol *pistol;
    
    MessageDispatcher *dispatcher;
    GameEntityManager *entityManager;
    
    Character* getIdleEnemyFromPool();
public:
    void reset();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithGameScene(GameScene *gs);
    BGTWorld();
    ~BGTWorld();
    // implement the "static create()" method manually
    void createWorld(unsigned int level);
    
    void update(float dt);
    
    void toggleWeapon();
    
    void wallDie();
    
    Vector<Character*> getMonsters();
    
    BGTWall* getWall();
    
    void onEnter();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
};

#endif /* defined(__BGT__BGTWorld__) */
