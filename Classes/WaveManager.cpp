//
//  WaveManager.cpp
//  BGT
//
//  Created by John Running on 15/3/23.
//
//

#include "WaveManager.h"

#include "json.h"
#include "Troop.h"
#include "Unit.h"

// singleton stuff
static WaveManager *s_SharedManager = NULL;

WaveManager::WaveManager()
{
    
}

WaveManager::~WaveManager()
{
    
}

bool WaveManager::init()
{
    auto sharedFileUtils = FileUtils::getInstance();
    std::string data = sharedFileUtils->getStringFromFile("levels.json");
    
    Json::Value value;
    Json::Reader reader;
    if (!reader.parse(data, value)){
        CCLOG("data.c_str():%s",data.c_str());
        CCLOGERROR("Json::Reader failed: %s", reader.getFormattedErrorMessages().c_str());
    } else {
        //        if (value.isObject() && value.isMember("ticket")) m_ticket = value["ticket"].asInt();
        //        res = true;
    }
    //std::string okString = value["result"].asString();
    //int expired = jsonValue["expired"].asInt();
    
    Json::Value arrayNotes=value["monsters"];
    
    for (int i=0; i < arrayNotes.size();i++)
    {
        log("add monster");
        MonsterData *data = MonsterData::create();
        data->name = arrayNotes[i]["name"].asString();
        data->life = arrayNotes[i]["life"].asInt();
        data->type = arrayNotes[i]["type"].asInt();
        data->attackSpeed = arrayNotes[i]["attackSpeed"].asFloat();
        data->moveSpeed = arrayNotes[i]["moveSpeed"].asInt();
        data->defense = arrayNotes[i]["defense"].asInt();
        data->attackRange = arrayNotes[i]["attackRange"].asInt();
        data->damage = arrayNotes[i]["damage"].asInt();
        data->exp = arrayNotes[i]["ep"].asInt();
        data->level = arrayNotes[i]["level"].asInt();
        data->baoji = arrayNotes[i]["baoji"].asFloat();
        data->shanbi = arrayNotes[i]["shanbi"].asFloat();
        
        Json::Value hitRectObj=arrayNotes[i]["hitRect"];
        data->hitRect = Rect(hitRectObj["x"].asInt(),hitRectObj["y"].asInt(),hitRectObj["width"].asInt(),hitRectObj["height"].asInt());
        
        Json::Value anchorPointObj=arrayNotes[i]["anchorPoint"];
        data->anchorPoint = Point(anchorPointObj["x"].asFloat(),anchorPointObj["y"].asFloat());
        
        monsterDatas.pushBack(data);
    }


    arrayNotes=value["levels"];
    for (int i = 0; i < arrayNotes.size();i++)
    {
        log("add level");
        LevelData *levelData = LevelData::create();
        levelData->id = arrayNotes[i]["id"].asInt();
        Json::Value wavesObj=arrayNotes[i]["waves"];
        for (int j = 0; j < wavesObj.size();j++)
        {
            Wave *wave = Wave::create();
            levelData->waves.pushBack(wave);
            wave->id = j;
            Json::Value troopsObj=wavesObj[j]["troops"];
            for (int k = 0; k < troopsObj.size();k++)
            {
                Troop *troop = Troop::create();
                wave->troops.pushBack(troop);
                troop->beginTime = troopsObj[k]["beginTime"].asFloat();
                troop->endTime = troopsObj[k]["endTime"].asFloat();
                troop->timeMode = (TroopTimeMode)troopsObj[k]["timeMode"].asInt();
                troop->positionMode = (TroopPositionMode)troopsObj[k]["positionMode"].asInt();
                troop->monsterTypeMode = (TroopMonsterMode)troopsObj[k]["monsterTypeMode"].asInt();
                Json::Value typesForRandomsObj=troopsObj[k]["typesForRandom"];
                for(int m = 0; m < typesForRandomsObj.size(); m++){
                    Value value = Value(typesForRandomsObj[m].asInt());
                    troop->typesForRandom.push_back(value);
                }
                Json::Value unitsObj=troopsObj[k]["units"];
                for(int m = 0; m < unitsObj.size(); m++){
                    Unit *unit = Unit::create();
                    unit->type = unitsObj[m]["type"].asInt();
                    unit->x = unitsObj[m]["x"].asInt();
                    unit->y = unitsObj[m]["y"].asInt();
                    unit->isRandomPosition = unitsObj[m]["isRandomPosition"].asBool();
                    troop->units.pushBack(unit);
                }
            }
        }
        levelDatas.pushBack(levelData);
    }
    return true;
}

LevelData* WaveManager::getLevelData(int index)
{
    return levelDatas.at(index);
}

Wave* WaveManager::getWave(LevelData *levelData,int index)
{
    return levelData->getWave(index);
}

WaveManager* WaveManager::getInstance()
{
    if (!s_SharedManager)
    {
        s_SharedManager = new WaveManager();
        s_SharedManager->init();
    }
    
    return s_SharedManager;
}

Vector<MonsterData*> WaveManager::getMonsterDatas()
{
    return monsterDatas;
}

MonsterData* WaveManager::getMonsterDataByType(int type)
{
    for (int i = 0; i < monsterDatas.size(); i++) {
        MonsterData *m = monsterDatas.at(i);
        if (m->type == type) {
            return m;
        }
    }
    return NULL;
}
