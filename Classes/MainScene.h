#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"

class Character;

#include "Obstacle.h"

enum class GameState
{
    Title,
    Ready,
    Playing,
    GameOver,
};

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void onEnter() override;
    void update(float dt) override;

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    std::vector<cocos2d::Rect> getGroundRects();
    
protected:
    Character* character;

private:
    cocos2d::Vector<Obstacle*> obstacles;
    cocos2d::Node* background;
    cocos2d::Node* ground;
    cocos2d::Sprite* ground1;
    cocos2d::Sprite* ground2;
    cocos2d::Vector<cocos2d::Sprite*> grounds;
    GameState gameState;
    
    void setupTouchHandling();
    void createObstacle(float dt);
    
    void triggerTitle();
    void triggerGameOver();
    void triggerPlaying();
    void triggerReady();
    void resetGameState();
};

#endif // __MainScene_SCENE_H__
