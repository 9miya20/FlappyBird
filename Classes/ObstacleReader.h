//
//  ObstacleReader.h
//  FlappyBird
//
//  Created by Shota Miyazato on 2016/05/12.
//
//

#ifndef __FlappyBird__ObstacleReader__
#define __FlappyBird__ObstacleReader__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class ObstacleReader : public cocostudio::NodeReader {
public:
    static ObstacleReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* defined(__FlappyBird__Obstacle__) */
