//
//  GameEntityManager.cpp
//  BGT
//
//  Created by John Running on 15/3/4.
//
//

#include "GameEntityManager.h"
#include "GameEntity.h"

static GameEntityManager *s_SharedManager = NULL;

//this must reside in the cpp file; otherwise, an instance will be created
//for every file in which the header is included
GameEntityManager* GameEntityManager::getInstance()
{
//    static GameEntityManager instance;
//    return &instance;
    
    if (!s_SharedManager)
    {
        s_SharedManager = new GameEntityManager();
        s_SharedManager->init();
    }
    
    return s_SharedManager;
}

bool GameEntityManager::init()
{
    
    return true;
}

//------------------------- GetEntityFromID -----------------------------------
//-----------------------------------------------------------------------------
GameEntity* GameEntityManager::getEntityFromID(int idV)
{
    //find the entity
    EntityMap::const_iterator ent = m_EntityMap.find(idV);
    
    //assert that the entity is a member of the map
    //assert ( (ent !=  m_EntityMap.end()) && "<EntityManager::GetEntityFromID>: invalid ID");
    CCASSERT(  (ent !=  m_EntityMap.end()) , "<EntityManager::GetEntityFromID>: invalid ID");
    return ent->second;
    return NULL;
}

void GameEntityManager::removeAllEntity()
{
    m_EntityMap.clear();
}

//--------------------------- RemoveEntity ------------------------------------
//-----------------------------------------------------------------------------
void GameEntityManager::removeEntity(GameEntity* pEntity)
{
    m_EntityMap.erase(m_EntityMap.find(pEntity->getID()));
}

//---------------------------- RegisterEntity ---------------------------------
//-----------------------------------------------------------------------------
void GameEntityManager::registerEntity(GameEntity* newEntity)
{
    m_EntityMap.insert(newEntity->getID(), newEntity);
    //m_EntityMap.insert(std::make_pair(newEntity->getID(), newEntity));
}
