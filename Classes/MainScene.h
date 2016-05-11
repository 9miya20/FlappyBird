#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"

class Character;

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void onEnter() override;

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
protected:
    Character* character;

private:
    void setupTouchHandling();
};

#endif // __MainScene_SCENE_H__
