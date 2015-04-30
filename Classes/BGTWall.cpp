//
//  BGTWall.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "BGTWall.h"
#include "AppDelegate.h"
#include "Character.h"
#include "GameEntityManager.h"

BGTWall::BGTWall()
:totalLife(0)
,life(0)
,lifeBar(NULL)
{
    
}

bool BGTWall::initWithWorld(BGTWorld *w){
    if (!GameEntity::initWithWorld(w)) {
        return false;
    }
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    width = fieldHeight * scaleFactory;
    
    Sprite *stone1 = Sprite::create("stone.png");
    this->addChild(stone1);
    stone1->setPosition(75,250);
    
    
    Sprite *rope = Sprite::create("rope.png");
    this->addChild(rope);
    rope->setPosition(0,0);
    
    Sprite *stone2 = Sprite::create("stone.png");
    this->addChild(stone2);
    stone2->setPosition(-50,-250);
    totalLife = 100;
    life = totalLife;
    return true;
}

float BGTWall::getLife()
{
    return life;
}

float BGTWall::getTotalLife()
{
    return totalLife;
}

void BGTWall::reset()
{
    life = totalLife;
}

float BGTWall::getWidth()
{
    return width;
}

void BGTWall::takeDamage(float damage){
    life -= damage;
    if (life < 0) {
        life = 0;
    }
    if (life <= 0) {
        life = 0;
        //dead
//        [[NSNotificationCenter defaultCenter] postNotificationName:@"wallDone" object:self];
        world->wallDie();
    }
}

bool BGTWall::handleMessage(const Telegram& msg)
{
    switch (msg.msg) {
        case Msg_WallDamaged:{
            //Character *monster = (Character*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
            float damage = *(float*)msg.extraInfo;
            log("takedamage:%f",damage);
            takeDamage(damage);
        }
            break;
        default:
            break;
    }
    return false;
}

void BGTWall::update(float dt){
    
}
