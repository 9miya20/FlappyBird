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
    this->isFlying = false;
    
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
    if (!this->isFlying) return;
    
    this->velocity += accel * dt;
    this->setPosition(this->getPosition() + Vec2(0, this->velocity * dt));
}

void Character::jump()
{
    this->velocity = JUMP_FORCE;
    
    /*
    this->stopAllActions();
    this->runAction(this->timeline);
    this->timeline->play("chop", false);
    */
    
    /*
    this->stopAllActions();
    this->runAction(this->timeline);
    auto repeat = Repeat::create(CallFunc::create([this]{
        this->timeline->play("fly", false);
    }), 3);
     */
    
    this->stopAllActions();
    this->runAction(this->timeline);
    this->timeline->play("fly", false);
    
    
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

void Character::SetIsFlying(bool isFlying){
    this->isFlying = isFlying;
}

