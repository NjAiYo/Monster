//
//  BGTTile.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "BGTTile.h"


BGTTile::BGTTile()
:_col(0)
,_row(0)
{
    
}

bool BGTTile::init(){
    _col = 0;
    _row = 0;
    
    return true;
}
