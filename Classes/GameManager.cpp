//
//  GameManager.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "GameManager.h"

// singleton stuff
static GameManager *s_SharedManager = NULL;

GameManager::GameManager()
:userData(NULL)
{
    
}

GameManager::~GameManager()
{
    
}

bool GameManager::init()
{
    
    return true;
}

GameManager* GameManager::getInstance()
{
    if (!s_SharedManager)
    {
        s_SharedManager = new GameManager();
        s_SharedManager->init();
    }
    
    return s_SharedManager;
}

void GameManager::readGameData()
{
    
}

void GameManager::saveGameData()
{
    
}
