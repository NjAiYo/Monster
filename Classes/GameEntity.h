//
//  Character.h
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#ifndef __BGT__GameEntity__
#define __BGT__GameEntity__

#include "cocos2d.h"
#include "Utils.h"
class BGTWorld;

USING_NS_CC;

class GameEntity : public cocos2d::Node
{
private:
    //every entity has a unique identifying number
    int          m_ID;
    
    //this is the next valid ID. Each time a GameEntity is instantiated
    //this value is updated
    static int  m_iNextValidID;
    
    //this is called within the constructor to make sure the ID is set
    //correctly. It verifies that the value passed to the method is greater
    //or equal to the next valid ID, before setting the ID and incrementing
    //the next valid ID
    void setID(int val);
    
protected:
    BGTWorld *world;
    
public:
    
    
    virtual ~GameEntity(){}
    
    BGTWorld* getWorld();
    
    int          getID()const{return m_ID;}
    
    virtual bool initWithWorld(BGTWorld *w);
    
    //all subclasses can communicate using messages.
    virtual bool  handleMessage(const Telegram& msg)=0;
    //all entities must implement an update function
    virtual void update(float dt)=0;
};

#endif /* defined(__BGT__GameEntity__) */
