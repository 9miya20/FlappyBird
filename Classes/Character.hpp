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
    
protected:
    cocostudio::timeline::ActionTimeline* timeline;
    
    bool isStart;
    float velocity;
    float accel;
};


#endif /* Character_hpp */
