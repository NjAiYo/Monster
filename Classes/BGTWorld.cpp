//
//  BGTWorld.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "BGTWorld.h"
#include "GameScene.h"
#include "AppDelegate.h"
#include "BGTWall.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "MessageDispatcher.h"
#include "Weapon.h"
#include "Pistol.h"
#include "Knife.h"

BGTWorld::BGTWorld()
:currentLevel(0)
{
    
}

BGTWorld::~BGTWorld()
{
    
}

void BGTWorld::reset()
{
    free(roads);
}

bool BGTWorld::initWithGameScene(GameScene *gs)
{
    if (!Node::init()) {
        return false;
    }
    gameScene = gs;
    entityManager = GameEntityManager::getInstance();
    dispatcher = MessageDispatcher::getInstance();
    return true;
}

void BGTWorld::onEnter()
{
    Node::onEnter();
}

//回放，枪蓄力，子弹，技能点，蓄力功能调整，浮空调整，记录保存，编辑器，出怪功能，掉落物品，能量，耐久度，必杀，qte,自动拾取
void BGTWorld::createWorld(unsigned int level){
    currentLevel = level;
    Size size = Director::getInstance()->getWinSize();
    MessageDispatcher::getInstance();
    bgLayer = Layer::create();
    addChild(bgLayer);
    
    battlefieldLayer = Layer::create();
    addChild(battlefieldLayer);
    
    weaponLayer = Layer::create();
    addChild(weaponLayer);
    
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    Sprite *sprite = Sprite::create("gamebg.jpg");
    float w = sprite->getContentSize().width;
    float h = sprite->getContentSize().height;
    sprite->setScaleX(size.width/w);
    sprite->setScaleY(size.height/h);
    bgLayer->addChild(sprite);
    
    sprite->setPosition(size.width/2,size.height/2);
    
    wall = new BGTWall();
    wall->initWithWorld(this);
    bgLayer->addChild(wall);
    wall->release();
    entityManager->registerEntity(wall);
    
    
    wall->setPosition(200*scaleFactory,600*scaleFactory);
    Vec2 wallPosition = wall->getPosition();
    
    float x1 = wallPosition.x + cosf(M_PI*-70.0f/180.0f)*wall->getWidth()/2;
    float y1 = wallPosition.y - sinf(M_PI*-70.0f/180.0f)*wall->getWidth()/2;
    
    wall->topPosition = Vec2(x1,y1);
    
    float x2 = wallPosition.x + cosf(M_PI*110.0f/180.0f)*wall->getWidth()/2;
    float y2 = wallPosition.y - sinf(M_PI*110.0f/180.0f)*wall->getWidth()/2;
    wall->bottomPosition = Vec2(x2,y2);
    
    auto draw = DrawNode::create();
    addChild(draw, 10);
    draw->drawLine(Vec2(x1,y1), Vec2(x2, y2), Color4F(0.0, 1.0, 0.0, 1.0));
    
    road0Y = y1;
    road1Y = wallPosition.y - sinf(M_PI*-70.0f/180.0f)*wall->getWidth()/4;
    road2Y = wallPosition.y;
    road3Y = wallPosition.y - sinf(M_PI*110.0f/180.0f)*wall->getWidth()/4;
    road4Y = y2;
    
    roads = (float*)malloc(sizeof(float)*5);
    roads[0] = road0Y;
    roads[1] = road1Y;
    roads[2] = road2Y;
    roads[3] = road3Y;
    roads[4] = road4Y;
    
    //create monsters put in right of screen
    int r = arc4random() % 5;
    
    
    for (int i = 0; i < 20; i++) {
        Character *enemy = new Character();
        enemy->initWithWorldAndType(this,CharacterTypeSmallZombie);
        battlefieldLayer->addChild(enemy);
        enemy->setVisible(false);
        enemy->release();
        monsterPool.pushBack(enemy);
        entityManager->registerEntity(enemy);
    }
    

    
    
    
    

//    star = Sprite::create("PIC_XX.png");
//    star->setPosition(Vec2(100, 100));
//    battlefieldLayer->addChild(star);
    //star->setTag(111);
    
    knife = new Knife();
    knife->initWithWorld(this);
    battlefieldLayer->addChild(knife);
    knife->release();
    weapons.pushBack(knife);
    
    pistol = new Pistol();
    pistol->initWithWorld(this);
    battlefieldLayer->addChild(pistol);
    pistol->release();
    weapons.pushBack(pistol);
    entityManager->registerEntity(knife);
    entityManager->registerEntity(pistol);
    
    currentWeapon = knife;
    
    
    
    Character *monster = getIdleEnemyFromPool();
    monster->setVisible(true);
    monster->setPosition(Vec2(size.width+arc4random()%100, roads[r]));
    monster->setFloor(roads[r]);
    monster->move();

}

Character* BGTWorld::getIdleEnemyFromPool(){
    Character *enemy = NULL;
    for (Character *monster : monsterPool) {
        if (!monster->isVisible()) {
            enemy = monster;
            break;
        }
    }
    if (!enemy) {
        enemy = new Character();
        enemy->initWithWorldAndType(this,CharacterTypeSmallZombie);
        battlefieldLayer->addChild(enemy);
        enemy->setVisible(false);
        enemy->release();
        monsterPool.pushBack(enemy);
        entityManager->registerEntity(enemy);
    }
    return enemy;
}

void BGTWorld::toggleWeapon()
{
    if (currentWeapon == knife) {
        currentWeapon = pistol;
    }else{
        currentWeapon = knife;
    }
}

void BGTWorld::wallDie()
{
    log("wallDie");
}

BGTWall* BGTWorld::getWall()
{
    return wall;
}

Vector<Character*> BGTWorld::getMonsters()
{
    return monsterPool;
}

void BGTWorld::update(float dt)
{
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible() || monster->isDieState()) {
            continue;
        }
        monster->update(dt);
    }
    currentWeapon->update(dt);
    wall->update(dt);
    dispatcher->dispatchDelayedMessages();
}

bool BGTWorld::onTouchBegan(Touch* touch, Event* event)
{
    currentWeapon->onTouchBegan(touch, event);
    

    return true;
}

void BGTWorld::onTouchMoved(Touch* touch, Event* event)
{
    currentWeapon->onTouchMoved(touch, event);

}

void BGTWorld::onTouchEnded(Touch* touch, Event* event)
{
    currentWeapon->onTouchEnded(touch, event);
}

void BGTWorld::onTouchCancelled(Touch *touch, Event *unused_event)
{
    currentWeapon->onTouchCancelled(touch, unused_event);
}
