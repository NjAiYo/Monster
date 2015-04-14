//
//  BGTMap.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "BGTMap.h"


BGTMap::BGTMap()
:currentLevel(0)
{
    
}

bool BGTMap::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    
    return true;
}



