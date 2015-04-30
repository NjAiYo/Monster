//
//  BGTWorld.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "BGTWorld.h"
#include "GameScene.h"
#include "AppDelegate.h"
#include "BGTWall.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "MessageDispatcher.h"
#include "Weapon.h"
#include "Pistol.h"
#include "Knife.h"
#include "CCShake.h"

BGTWorld::BGTWorld()
:currentLevelIndex(-1)
,currentWaveIndex(-1)
,currentWave(NULL)
,gameBgSprite(NULL)
{
    
}

BGTWorld::~BGTWorld()
{
    free(roads);
}

bool BGTWorld::initWithGameScene(GameScene *gs)
{
    if (!Node::init()) {
        return false;
    }
    waveManager = WaveManager::getInstance();
    gameScene = gs;
    entityManager = GameEntityManager::getInstance();
    dispatcher = MessageDispatcher::getInstance();

    bgLayer = Layer::create();
    addChild(bgLayer);
    
    battlefieldLayer = Layer::create();
    addChild(battlefieldLayer);
    
    monsterLayer = Layer::create();
    battlefieldLayer->addChild(monsterLayer);
    
    weaponLayer = Layer::create();
    addChild(weaponLayer);
    
    wall = new BGTWall();
    wall->initWithWorld(this);
    bgLayer->addChild(wall,1);
    wall->release();
    entityManager->registerEntity(wall);
    
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    wall->setPosition(150*scaleFactory,500*scaleFactory);
    Vec2 wallPosition = wall->getPosition();
    
    float x1 = wallPosition.x + cosf(M_PI*-70.0f/180.0f)*wall->getWidth()/2;
    float y1 = wallPosition.y - sinf(M_PI*-70.0f/180.0f)*wall->getWidth()/2;
    wall->topPosition = Vec2(x1,y1);
    
    float x2 = wallPosition.x + cosf(M_PI*110.0f/180.0f)*wall->getWidth()/2;
    float y2 = wallPosition.y - sinf(M_PI*110.0f/180.0f)*wall->getWidth()/2;
    wall->bottomPosition = Vec2(x2,y2);
    
    auto draw = DrawNode::create();
    addChild(draw, 10);
    draw->drawLine(Vec2(x1,y1), Vec2(x2, y2), Color4F(0.0, 1.0, 0.0, 1.0));
    
    road0Y = y1;
    road1Y = wallPosition.y - sinf(M_PI*-70.0f/180.0f)*wall->getWidth()/4;
    road2Y = wallPosition.y;
    road3Y = wallPosition.y - sinf(M_PI*110.0f/180.0f)*wall->getWidth()/4;
    road4Y = y2;
    
    roads = (float*)malloc(sizeof(float)*5);
    roads[0] = road0Y;
    roads[1] = road1Y;
    roads[2] = road2Y;
    roads[3] = road3Y;
    roads[4] = road4Y;
    
    knife = new Knife();
    knife->initWithWorld(this);
    battlefieldLayer->addChild(knife,10000);
    knife->release();
    weapons.pushBack(knife);
    
    pistol = new Pistol();
    pistol->initWithWorld(this);
    battlefieldLayer->addChild(pistol,10000);
    pistol->release();
    weapons.pushBack(pistol);
    entityManager->registerEntity(knife);
    entityManager->registerEntity(pistol);

    Size size = Director::getInstance()->getWinSize();
    uiLayer = Layer::create();
    addChild(uiLayer);
    waveTip = Label::create("一大波怪物正在靠近", "Arial", 120*scaleFactory);
    waveTip->setColor(Color3B(255, 255, 255));
    uiLayer->addChild(waveTip);
    waveTip->setPosition(size.width/2+size.width, size.height/2);
    waveTip->setVisible(false);
    
    return true;
}

void BGTWorld::onEnter()
{
    Node::onEnter();
}

void BGTWorld::onEnterTransitionDidFinish()
{
    Node::onEnterTransitionDidFinish();
}

void BGTWorld::onExit()
{
    Node::onExit();
}

void BGTWorld::onExitTransitionDidStart()
{
    Node::onExitTransitionDidStart();
}

//回放，枪蓄力，子弹，技能点，蓄力功能调整，浮空调整，记录保存，编辑器，出怪功能，掉落物品，能量，耐久度，必杀，qte,自动拾取
void BGTWorld::createWorld(int level){
    currentLevelIndex = level;
    Size size = Director::getInstance()->getWinSize();
    


    if(gameBgSprite && gameBgSprite->getTag()!=currentLevelIndex){
        gameBgSprite->removeFromParent();
    }
    if(!gameBgSprite){
        gameBgSprite = Sprite::create("gamebg.jpg");
        gameBgSprite->setTag(currentLevelIndex);
        float w = gameBgSprite->getContentSize().width;
        float h = gameBgSprite->getContentSize().height;
        gameBgSprite->setScaleX(size.width/w);
        gameBgSprite->setScaleY(size.height/h);
        bgLayer->addChild(gameBgSprite,0);
        
        gameBgSprite->setPosition(size.width/2,size.height/2);
    }
    wall->reset();
    
    for(int i = 0; i < monsterPool.size(); i++){
        Character *enemy = monsterPool.at(i);
        enemy->setTag(-1);
    }
    
    
    currentLevelData = waveManager->getLevelData(currentLevelIndex);
    for (int i = 0; i < currentLevelData->waves.size(); i++) {
        Wave *wave = currentLevelData->waves.at(i);
        
        //为这次的战斗生成怪物数据
        wave->generateUnitsDataForBattle();
        Vector<Unit*> allUnits = wave->getAllUnits();
        //根据数据生出怪物对象池
        for (int j = 0; j < allUnits.size(); j++) {
            Unit *unit = allUnits.at(j);
            getIdleEnemyByTypeFromPoolForInit(unit->outType);
//            Character *enemy = getIdleEnemyByTypeFromPoolForInit(unit->outType);
//            enemy->setPosition(Vec2(size.width+unit->outPosition.x+50, wall->bottomPosition.y+unit->outPosition.y));
//            enemy->setFloor(wall->bottomPosition.y+unit->outPosition.y);
        }
    }
    
    currentWeapon = knife;
    

//    Character *monster = getIdleEnemyFromPool();
//    monster->setVisible(true);
//    monster->setPosition(Vec2(size.width+arc4random()%100, roads[r]));
//    monster->setFloor(roads[r]);
//    monster->move();
    
    //shake(0.1f,5);
}

void BGTWorld::shake( float d, float strength )
{
    CCShake* shake = CCShake::create(d,strength);
    shake->setTag(145);
    this->stopActionByTag(145);
    this->setPosition(Vec2(0,0));
    this->runAction(shake);
}

Character* BGTWorld::getIdleEnemyByTypeFromPoolForInit(int type){
    Character *enemy = NULL;
    for (Character *monster : monsterPool) {
        if (monster->getTag()==-1 && monster->getType() == type) {
            enemy = monster;
            break;
        }
    }
    if (!enemy) {
        enemy = new Character();
        enemy->initWithWorldAndType(this,(CharacterType)type);
        monsterLayer->addChild(enemy);
        enemy->setVisible(false);
        enemy->setTag(-1);
        enemy->release();
        monsterPool.pushBack(enemy);
        entityManager->registerEntity(enemy);
    }
    return enemy;
}

Character* BGTWorld::getIdleEnemyByTypeFromPool(int type){
    Character *enemy = NULL;
    for (Character *monster : monsterPool) {
        if (!monster->isVisible() && monster->getType() == type) {
            enemy = monster;
            break;
        }
    }
    if (!enemy) {
        enemy = new Character();
        enemy->initWithWorldAndType(this,(CharacterType)type);
        monsterLayer->addChild(enemy);
        enemy->setVisible(false);
        enemy->release();
        monsterPool.pushBack(enemy);
        entityManager->registerEntity(enemy);
    }
    return enemy;
}

void BGTWorld::toggleWeapon()
{
    if (currentWeapon == knife) {
        currentWeapon = pistol;
    }else{
        currentWeapon = knife;
    }
}

void BGTWorld::wallDie()
{
    endGame(false);
}

BGTWall* BGTWorld::getWall()
{
    return wall;
}

Vector<Character*> BGTWorld::getMonsters()
{
    return monsterPool;
}

void BGTWorld::reset()
{
    currentWaveIndex = -1;
    timePast = 0;
    totalKilledNum = 0;
    waveEnemyNumLeftToBeOut = 0;
    waveKilledNum = 0;
    nextWaveOutTimeLeft = 0.1;
    showedNextWaveUI = false;
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {
            continue;
        }
        monster->resumeAnimation();
    }
}

void BGTWorld::startGame()
{
    reset();
}

void BGTWorld::endGame(bool isWin)
{
    gameScene->gameEnd(isWin);
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {
            continue;
        }
        monster->pauseAnimation();
    }
}

void BGTWorld::nextWave(){
    currentWaveIndex++;
    timePast = 0;
    showedNextWaveUI = false;
    log("%d:currentLevelData->waves=%zd",currentWaveIndex,currentLevelData->waves.size());
    if (currentWaveIndex < currentLevelData->waves.size()) {
        currentWave = currentLevelData->getWave(currentWaveIndex);
        Vector<Unit*> allUnits = currentWave->getAllUnits();
        log("allUnits.size()=%zd",allUnits.size());
        waveEnemyNumLeftToBeOut = (unsigned int)allUnits.size();
        waveKilledNum = 0;
    }
}

void BGTWorld::monsterDied(Character* monster)
{
    totalKilledNum++;
    waveKilledNum++;
    if(waveKilledNum >= currentWave->getAllUnits().size()){
        if(currentWaveIndex == currentLevelData->waves.size()-1){
            //最后一波的所有怪都杀了
            CallFunc *func = CallFunc::create([=](){
                endGame(true);
            });
            waveTip->runAction(Sequence::create(DelayTime::create(1.0),func, NULL));
        }else{
            //这一波怪物都被杀了
            if (nextWaveOutTimeLeft > 4) {
                nextWaveOutTimeLeft = 4;
                //showNextWaveUI();
            }
        }
    }
}

void BGTWorld::showNextWaveUI(){
    waveTip->setVisible(true);
    Size size = Director::getInstance()->getWinSize();
    waveTip->setPosition(size.width/2+size.width, size.height/2);
    waveTip->runAction(Sequence::create(DelayTime::create(1.0),MoveBy::create(0.5, Vec2(-size.width,0)),DelayTime::create(1.0),MoveBy::create(0.5, Vec2(-size.width,0)), NULL));
}

void BGTWorld::resumeGame(){
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {
            continue;
        }
        monster->resumeAnimation();
    }
}

void BGTWorld::pauseGame(){
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {
            continue;
        }
        monster->pauseAnimation();
    }
}

void BGTWorld::update(float dt)
{
    timePast += dt;
    if (nextWaveOutTimeLeft > 0) {
        //log("nextWaveOutTimeLeft:%f",nextWaveOutTimeLeft);
        nextWaveOutTimeLeft -= dt;
        if(nextWaveOutTimeLeft <=4 && nextWaveOutTimeLeft>3 && !showedNextWaveUI){
            showNextWaveUI();
            showedNextWaveUI = true;
        }
        if(nextWaveOutTimeLeft <=0){
            nextWave();
        }
    }


    //put next enemy to battle field
    if(currentWave){
        Size size = Director::getInstance()->getWinSize();
        Vector<Unit*> allUnits = currentWave->getAllUnits();
        //根据数据生出怪物对象池
        for (int j = 0; j < allUnits.size(); j++) {
            Unit *unit = allUnits.at(j);
            if (unit->outed) {
                continue;
            }
            if (unit->outTime <= timePast) {
                Character *monster = getIdleEnemyByTypeFromPool(unit->outType);
                monster->reset();
                monster->setPosition(Vec2(size.width+unit->outPosition.x+50, wall->bottomPosition.y+unit->outPosition.y));
                monster->setFloor(wall->bottomPosition.y+unit->outPosition.y);
                monster->setLocalZOrder(9999-(wall->bottomPosition.y+unit->outPosition.y));
                monster->setVisible(true);
                monster->move();
                unit->outed = true;
                waveEnemyNumLeftToBeOut--;
                if(waveEnemyNumLeftToBeOut<=0){
                    //这一波所有的怪物都出击了,
                    nextWaveOutTimeLeft = waveGapTime;
                }
                log("put monster to field:type=%d,x=%f,y=%f",unit->outType,monster->getPositionX(),monster->getPositionY());
            }
        }
    }
    for(Character *monster : monsterPool)
    {
        if (!monster->isVisible()) {
            continue;
        }
        monster->update(dt);
    }
    currentWeapon->update(dt);
    wall->update(dt);
    dispatcher->dispatchDelayedMessages();
}

bool BGTWorld::onTouchBegan(Touch* touch, Event* event)
{
    currentWeapon->onTouchBegan(touch, event);
    

    return true;
}

void BGTWorld::onTouchMoved(Touch* touch, Event* event)
{
    currentWeapon->onTouchMoved(touch, event);

}

void BGTWorld::onTouchEnded(Touch* touch, Event* event)
{
    currentWeapon->onTouchEnded(touch, event);
}

void BGTWorld::onTouchCancelled(Touch *touch, Event *unused_event)
{
    currentWeapon->onTouchCancelled(touch, unused_event);
}
