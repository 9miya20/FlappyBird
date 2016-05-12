//
//  ObstacleReader.cpp
//  FlappyBird
//
//  Created by Shota Miyazato on 2016/05/12.
//
//

#include "ObstacleReader.h"
#include "Obstacle.h"

using namespace cocos2d;

static ObstacleReader* _instanceObstacleReader = nullptr;

ObstacleReader* ObstacleReader::getInstance() {
    if (!_instanceObstacleReader) {
        _instanceObstacleReader = new ObstacleReader();
    }
    return _instanceObstacleReader;
}

void ObstacleReader::purge() {
    CC_SAFE_DELETE(_instanceObstacleReader);
}

Node* ObstacleReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions) {
    Obstacle* node = Obstacle::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}
