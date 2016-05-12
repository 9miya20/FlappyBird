//
//  Obstacle.h
//  FlappyBird
//
//  Created by Shota Miyazato on 2016/05/12.
//
//

#ifndef __FlappyBird__Obstacle__
#define __FlappyBird__Obstacle__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class Obstacle : public cocos2d::Node {
public:
    CREATE_FUNC(Obstacle);
    bool init() override;
    void moveLeft(float distance);
    std::vector<cocos2d::Rect> getRects();

protected:
    cocostudio::timeline::ActionTimeline* timeline;

    void onEnter() override;
    void onExit() override;
    
private:
    cocos2d::Node* pipe_top;
    cocos2d::Node* pipe_bottom;
    

};

#endif /* defined(__FlappyBird__Obstacle__) */
