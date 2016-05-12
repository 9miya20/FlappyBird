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
    
    auto ground = this->background->getChildByName("ground");
    ground->setZOrder(1);

    return true;
}

void MainScene::onEnter()
{
    Layer::onEnter();
    
    this->setupTouchHandling();
    
    this->scheduleUpdate();
    
    this->schedule(CC_SCHEDULE_SELECTOR(MainScene::createObstacle), OBSTACLE_TIME_SPAN);
}

void MainScene::update(float dt)
{
    for (auto obstacle : this->obstacles) {
        obstacle->moveLeft(SCROOL_SPEED_X * dt);
    }
    
    Rect characterRect = this->character->getRect();
    for (auto obstacle : this->obstacles) {
        auto obstacleRects = obstacle->getRects();
        for (Rect obstacleRect : obstacleRects) {
            bool hit = characterRect.intersectsRect(obstacleRect);
            if (hit) {
                //CCLOG("Hit");
                this->unscheduleAllCallbacks();
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
        this->character->jump();
        
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
