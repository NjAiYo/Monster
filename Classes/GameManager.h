//
//  GameManager.h
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#ifndef __BGT__GameManager__
#define __BGT__GameManager__

#include "cocos2d.h"
//#include "sqlite3.h"
#include "UserData.h"
#include "Player.h"

USING_NS_CC;

//管理用户数据

class GameManager : public cocos2d::Ref
{
private:
//    sqlite3 *pDB;
    
    char * errMsg;
    
//    std::string sqlstr;
    int result;
    
    Player *player;
    UserData *userData;
    
    GameManager(const GameManager &);
    GameManager& operator=(const GameManager &);
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    GameManager();
    virtual ~GameManager();
    virtual bool init();
    static GameManager* getInstance();
    void readGameData();
    void saveGameData();
    Player* getPlayer();
    
};

#endif /* defined(__BGT__GameManager__) */
