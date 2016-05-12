
//  Obstacle.cpp
//  FlappyBird
//
//  Created by Shota Miyazato on 2016/05/12.
//
//

#include "Obstacle.h"

using namespace cocos2d;

#pragma mark - Public methods

bool Obstacle::init() {
    if (!Node::init()) {
        return false;
    }

    return true;
}

#pragma mark - Private methods

#pragma mark View lifecycle

void Obstacle::onEnter()
{
    Node::onEnter();
    
    this->pipe_top = this->getChildByName("pipe_top");
    this->pipe_bottom =this->getChildByName("pipe_bottom");
}

void Obstacle::onExit()
{
    Node::onExit();
}


void Obstacle::moveLeft(float distance)
{
    this->setPosition(this->getPosition() + Vec2(-distance, 0));
}

std::vector<cocos2d::Rect> Obstacle::getRects()
{
    std::vector<Rect> rects;
        
    Rect rect1 = Rect(this->getPosition().x - this->pipe_top->getContentSize().width / 2, this->getPosition().y + this->pipe_top->getPosition().y, this->pipe_top->getContentSize().width, this->pipe_top->getContentSize().height);
    
    Rect rect2 = Rect(this->getPosition().x - this->pipe_bottom->getContentSize().width / 2, this->getPosition().y - this->pipe_top->getPosition().y - this->pipe_bottom->getContentSize().height, this->pipe_bottom->getContentSize().width, this->pipe_bottom->getContentSize().height);
    
    rects.push_back(rect1);
    rects.push_back(rect2);
    
    return rects;
}