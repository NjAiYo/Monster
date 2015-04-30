//
//  GameEntityManager.h
//  BGT
//
//  Created by John Running on 15/3/4.
//
//

#ifndef __BGT__GameEntityManager__
#define __BGT__GameEntityManager__

#include "cocos2d.h"
class GameEntity;

USING_NS_CC;

class GameEntityManager : public Ref
{
private:
    //to save the ol' fingers
    //typedef std::map<int, GameEntity*> EntityMap;
    typedef Map<int, GameEntity*> EntityMap;
    
    
    //to facilitate quick lookup the entities are stored in a std::map, in
    //which pointers to entities are cross-referenced by their identifying
    //number
    EntityMap           m_EntityMap;
    
    //copy ctor and assignment should be private
    GameEntityManager(const GameEntityManager &);
    GameEntityManager& operator=(const GameEntityManager &);
    

    GameEntityManager(){}
public:
    virtual bool init();
    static GameEntityManager* getInstance();

    //this method stores a pointer to the entity in the std::vector
    //m_Entities at the index position indicated by the entity's ID
    //(makes for faster access)
    void  registerEntity(GameEntity* newEntity);
    
    //returns a pointer to the entity with the ID given as a parameter
    GameEntity* getEntityFromID(int idV);
    
    //this method removes the entity from the list
    void removeEntity(GameEntity* pEntity);
    void removeAllEntity();
};

#endif /* defined(__BGT__GameEntityManager__) */
