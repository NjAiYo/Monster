//
//  LevelData.cpp
//  Monster
//
//  Created by John Running on 15/4/27.
//
//

#include "LevelData.h"

LevelData::LevelData()
:id(0)
{
    
}

Wave* LevelData::getWave(int index)
{
    return waves.at(index);
}
