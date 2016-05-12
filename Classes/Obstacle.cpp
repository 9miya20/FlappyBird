
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

    // load the character animation timeline
    this->timeline = cocos2d::CSLoader::createTimeline("Obstacle.csb");
    // retain the character animation timeline so it doesn't get deallocated
    this->timeline->retain();

    return true;
}

#pragma mark - Private methods

#pragma mark View lifecycle

void Obstacle::onEnter()
{
    Node::onEnter();
}

void Obstacle::onExit()
{
    Node::onExit();
}


void Obstacle::moveLeft(float distance)
{
    this->setPosition(this->getPosition() + Vec2(-distance, 0));
}