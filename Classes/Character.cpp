//
//  Character.cpp
//  FlappyBird
//
//  Created by Shota Miyazato on 2016/05/11.
//
//

#include "Character.hpp"
#include "Constants.h"

using namespace cocos2d;

bool Character::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    this->velocity = 0;
    this->accel = GRAVITY_ACCEL;
    
    // キャラクターのアニメーションのタイムラインを読み込む
    this->timeline = cocos2d::CSLoader::createTimeline("Character.csb");
    
    // キャラクターのアニメーションのタイムラインを確保し、メモリ領域が解放されないようにする
    this->timeline->retain();
    
    return true;
}

void Character::onEnter()
{
    Node::onEnter();
    
    this->bird = this->getChildByName("bird");
    this->scheduleUpdate();
}

void Character::update(float dt)
{
    if (!this->isStart) return;
    
    this->velocity += accel * dt;
    this->setPosition(this->getPosition() + Vec2(0, this->velocity * dt));
}

void Character::jump()
{
    if (!this->isStart) {
        this->isStart = true;
    }
    
    this->velocity = JUMP_FORCE;
}

cocos2d::Rect Character::getRect()
{
    auto birdContentSize = this->bird->getContentSize() * 0.8f;
    
    Rect rect = Rect(this->getPosition().x - birdContentSize.width / 2, this->getPosition().y - birdContentSize.height / 2, birdContentSize.width, birdContentSize.height);
    
    /*
    auto pipeTopRect = this->bird->getBoundingBox();
    pipeTopRect.origin += pipeTopRect;
     */
    
    return rect;
}

