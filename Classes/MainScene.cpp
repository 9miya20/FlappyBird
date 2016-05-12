#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CharacterReader.hpp"
#include "Character.hpp"
#include "ObstacleReader.h"
#include "Obstacle.h"
#include "Constants.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    CSLoader* instance = CSLoader::getInstance();
    instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
    instance->registReaderObject("ObstacleReader", (ObjectFactory::Instance) ObstacleReader::getInstance);
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    Size size = Director::getInstance()->getVisibleSize();
    rootNode->setContentSize(size);
    ui::Helper::doLayout(rootNode);
    addChild(rootNode);
    
    this->background = rootNode->getChildByName("back");
    
    this->character = this->background->getChildByName<Character*>("character");
    this->character->setZOrder(1);
    
    this->ground = this->background->getChildByName("groundNode");
    this->ground->setZOrder(1);
    
    this->ground1 = this->ground->getChildByName<Sprite*>("ground1");
    this->ground2 = this->ground->getChildByName<Sprite*>("ground2");
    this->grounds.pushBack(ground1);
    this->grounds.pushBack(ground2);

    return true;
}

void MainScene::onEnter()
{
    Layer::onEnter();
    
    this->setupTouchHandling();
    
    this->scheduleUpdate();
    
    this->triggerReady();
}

void MainScene::update(float dt)
{
    if (this->gameState != GameState::Playing) {
        return;
    }
    
    for (auto obstacle : this->obstacles) {
        obstacle->moveLeft(SCROOL_SPEED_X * dt);
    }
    
    this->ground1->setPosition(this->ground1->getPosition() + Vec2(-SCROOL_SPEED_X * dt, 0));
    this->ground2->setPosition(this->ground2->getPosition() + Vec2(-SCROOL_SPEED_X * dt, 0));
    if (this->grounds.back()->getPosition().x <= 0) {
        this->grounds.front()->setPositionX(this->grounds.back()->getPosition().x + this->grounds.front()->getContentSize().width);
        
        grounds.swap(this->grounds.front(), this->grounds.back());
    }
    
    Rect characterRect = this->character->getRect();
    for (auto obstacle : this->obstacles) {
        auto obstacleRects = obstacle->getRects();
        
        for (Rect obstacleRect : obstacleRects) {
            bool hit = characterRect.intersectsRect(obstacleRect);
            if (hit) {
                //CCLOG("Hit");
                //this->unscheduleAllCallbacks();
                this->triggerGameOver();
            } else {
                //CCLOG("Not Hit");
            }
        }
    }
    
    for (auto ground : this->grounds) {
        auto groundRects = this->getGroundRects();
        
        for (Rect groundRect : groundRects) {
            bool hit = characterRect.intersectsRect(groundRect);
            if (hit) {
                this->triggerGameOver();
            } else {
                //CCLOG("Not Hit");
            }
        }
    }
}

void MainScene::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        switch (this->gameState) {
            case::GameState::Title:
                break;
            case::GameState::Ready:
                this->triggerPlaying();
                break;
            case::GameState::Playing:
                this->character->jump();
                break;
            case::GameState::GameOver:
                auto nextGameScene = MainScene::createScene();
                auto transition = TransitionFade::create(1.0f, nextGameScene);
                Director::getInstance()->replaceScene(transition);
                break;
        }
        
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void MainScene::createObstacle(float dt)
{
    Obstacle* obstacle = dynamic_cast<Obstacle*>(CSLoader::createNode("Obstacle.csb"));
    this->obstacles.pushBack(obstacle);

    this->background->addChild(obstacle);
    
    float y = CCRANDOM_0_1() * (OBSTACLE_MAX_Y - OBSTACLE_MIN_Y) + OBSTACLE_MIN_Y;
    
    obstacle->setPosition(OBSTACLE_INIT_X, y);
    
    if (this->obstacles.size() > OBSTACLE_LIMIT) {
        this->obstacles.front()->removeFromParent();
        this->obstacles.erase(this->obstacles.begin());
    }
    
}

void MainScene::triggerTitle(){
    this->gameState = GameState::Title;
}

void MainScene::triggerGameOver(){
    this->gameState = GameState::GameOver;
    
    this->unschedule(CC_SCHEDULE_SELECTOR(MainScene::createObstacle));
}

void MainScene::triggerPlaying(){
    this->gameState = GameState::Playing;
    this->character->SetIsFlying(true);
    
    this->schedule(CC_SCHEDULE_SELECTOR(MainScene::createObstacle), OBSTACLE_TIME_SPAN);
}

void MainScene::triggerReady(){
    this->gameState = GameState::Ready;
    this->character->SetIsFlying(false);
}

void MainScene::resetGameState(){
    
}

std::vector<cocos2d::Rect> MainScene::getGroundRects()
{
    std::vector<Rect> rects;
    
    Rect rect1 = Rect(this->ground1->getPosition().x, 0, this->ground1->getContentSize().width, this->ground1->getContentSize().height);
    
    Rect rect2 = Rect(this->ground2->getPosition().x, 0, this->ground2->getContentSize().width, this->ground2->getContentSize().height);
    
    rects.push_back(rect1);
    rects.push_back(rect2);
    
    return rects;
}

