//
//  WaveManager.h
//  BGT
//
//  Created by John Running on 15/3/23.
//
//

#ifndef __BGT__WaveManager__
#define __BGT__WaveManager__


//1,一关有若干波数Wave，每一波含有若干队伍Troop，队伍有很多士兵Unit，每个队伍会一起出 ，队伍可以分配队形，默认一个队伍一个士兵，每个士兵出兵时间点在编辑器定好，时间点可以加一个随机范围，这个点出的兵可以是随机的，除了boss是固定的
//每一波有哪些兵种可出，兵种数量分配，原则上出兵从低级到高级兵出，出兵可以按阵型出


#include "cocos2d.h"
#include "MonsterData.h"
#include "LevelData.h"
USING_NS_CC;

//管理关卡

class WaveManager : public cocos2d::Ref
{
private:
    WaveManager(const WaveManager &);
    WaveManager& operator=(const WaveManager &);
    Vector<MonsterData*> monsterDatas;
    Vector<LevelData*> levelDatas;
    LevelData *currentLevelData;
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    WaveManager();
    virtual ~WaveManager();
    virtual bool init();
    static WaveManager* getInstance();
    
    
    LevelData* getLevelData(int index);
    Wave* getWave(LevelData *levelData,int index);
    
    Vector<MonsterData*> getMonsterDatas();
    MonsterData* getMonsterDataByType(int type);
};

#endif /* defined(__BGT__WaveManager__) */
