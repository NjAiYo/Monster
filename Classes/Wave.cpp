//
//  Wave.cpp
//  Monster
//
//  Created by John Running on 15/4/27.
//
//

#include "Wave.h"
#include "Unit.h"
#include "AppDelegate.h"

Wave::Wave()
:id(0)
{
    
}

void Wave::generateUnitsDataForBattle()
{
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    allUnits.clear();
    for (int i = 0; i < troops.size(); i++) {
        Troop *troop = troops.at(i);
        float delta = troop->endTime - troop->beginTime;
        float gapTime = delta / (float)troop->units.size();
        for (int j = 0; j < troop->units.size(); j++) {
            Unit *unit = troop->units.at(j);
            if(troop->timeMode == TROOP_TIME_MODE_FIXED){
                unit->outTime = troop->beginTime;
            }else if(troop->timeMode == TROOP_TIME_MODE_RANDOM){
                unit->outTime = troop->beginTime + CCRANDOM_0_1()*delta;
            }else if(troop->timeMode == TROOP_TIME_MODE_LINEAR){
                unit->outTime = troop->beginTime + gapTime * j;
            }
            
            if (troop->positionMode == TROOP_POSITION_MODE_FIXED) {
                unit->outPosition = Vec2(unit->x,unit->y);
            }else{
                unit->outPosition = Vec2(CCRANDOM_0_1()*fieldHeight * scaleFactory,CCRANDOM_0_1()*fieldHeight * scaleFactory);
            }
            
            if (troop->monsterTypeMode == TROOP_MONSTER_TYPE_MODE_FIXED) {
                unit->outType = unit->type;
            }else{
                if(troop->typesForRandom.size()==0){
                    unit->outType = 0;
                }else{
                    int len = (int)troop->typesForRandom.size();
                    int index = arc4random() % len;
                    Value value = troop->typesForRandom.at(index);
                    unit->outType = value.asInt();
                }
            }
            unit->outed = false;
            allUnits.pushBack(unit);
        }
    }
}

Vector<Unit*> Wave::getAllUnits()
{
    return allUnits;
}
