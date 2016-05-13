//
//  Character.hpp
//  FlappyBird
//
//  Created by Shota Miyazato on 2016/05/11.
//
//

#ifndef Character_hpp
#define Character_hpp

#include "cocostudio/CocoStudio.h"

class Character : public cocos2d::Node
{
public:
    CREATE_FUNC(Character);
    bool init() override;
    void onEnter() override;
    void update(float dt) override;
    void jump();
    cocos2d::Rect getRect();
    
    void SetIsFlying(bool isFlying);
    void SetVelocity(float velocity);
    
protected:
    cocostudio::timeline::ActionTimeline* timeline;
    
    bool isFlying;
    float velocity;
    float accel;
    
private:
    cocos2d::Node* bird;
};


#endif /* Character_hpp */
