//
//  Pistol.cpp
//  BGT
//
//  Created by John Running on 15/3/14.
//
//

#include "Pistol.h"
#include <SimpleAudioEngine.h>
#include "BGTWorld.h"
#include "Character.h"
#include "MessageDispatcher.h"
#include "AppDelegate.h"

bool Pistol::initWithWorld(BGTWorld *w)
{
    if (Weapon::initWithWorld(w)) {
        type = WeaponTypePistol;
        
        shotInteval = 250;
        canShot = true;
        xuliTotalTime = 500;//2秒
        xuliTimePast = 0;
        origDamage = 10;
        damage = origDamage;
        isXuliDamage = false;
        return true;
    }
    return false;
}

//all subclasses can communicate using messages.
bool Pistol::handleMessage(const Telegram& msg)
{
    return false;
}

//all entities must implement an update function
void Pistol::update(float dt)
{
    if (!canShot) {
        if (millisecondNow() - lastShotTime >= shotInteval) {
            canShot = true;
        }
    }
}

bool Pistol::onTouchBegan(Touch* touch, Event* event)
{
    log("Pistol::onTouchBegan");
    if (!canShot) {
        return true;
    }
    lastShotTime = millisecondNow();
    Vec2 pos = touch->getLocation();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jq.mp3");
    canShot = false;
    
    //hit test monster
    for (Character *agent : world->getMonsters()) {
        if (!agent->isVisible() || agent->isDieState()) {
            continue;
        }
        Rect rect = agent->getRect();
        bool hit = false;
        if (pos.x < rect.origin.x || pos.y < rect.origin.y || pos.x > rect.origin.x+rect.size.width || pos.y > rect.origin.y+rect.size.height) {
            hit = false;
        }else{
            hit = true;
        }
        if (hit) {
            MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                              getID(),           //sender ID
                                                              agent->getID(),           //receiver ID
                                                              Msg_AttackedByWeapon,        //msg
                                                              NULL);
        }
    }
    return true;
}

void Pistol::onTouchMoved(Touch* touch, Event* event)
{
    if (!canShot) {
        return;
    }
//    lastShotTime = millisecondNow();
//    Vec2 pos = touch->getLocation();
//    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jq.mp3");
//    canShot = false;
//    
//    //hit test monster
//    for (Character *agent : world->getMonsters()) {
//        if (!agent->isVisible()) {
//            continue;
//        }
//        Rect rect = agent->getRect();
//        bool hit = false;
//        if (pos.x < rect.origin.x || pos.y < rect.origin.y || pos.x > rect.origin.x+rect.size.width || pos.y > rect.origin.y+rect.size.height) {
//            hit = false;
//        }else{
//            hit = true;
//        }
//        if (hit) {
//            MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
//                                                              getID(),           //sender ID
//                                                              agent->getID(),           //receiver ID
//                                                              Msg_AttackedByWeapon,        //msg
//                                                              NULL);
//        }
//    }
}

void Pistol::onTouchEnded(Touch* touch, Event* event)
{
    
}

void Pistol::onTouchCancelled(Touch *touch, Event *unused_event)
{
    
}