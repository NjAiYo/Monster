//
//  Character.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "GameEntity.h"

int GameEntity::m_iNextValidID = 0;

bool GameEntity::initWithWorld(BGTWorld *w)
{
    if(!Node::init()) return false;
    world = w;
    setID(GameEntity::m_iNextValidID);
    return true;
}

BGTWorld* GameEntity::getWorld()
{
    return world;
}

void GameEntity::setID(int val)
{
    //make sure the val is equal to or greater than the next available ID
    //assert ( (val >= m_iNextValidID) && "<GameEntity::SetID>: invalid ID");
    CCASSERT( (val >= m_iNextValidID) , "<GameEntity::SetID>: invalid ID");
    m_ID = val;
    
    m_iNextValidID = m_ID + 1;
}

