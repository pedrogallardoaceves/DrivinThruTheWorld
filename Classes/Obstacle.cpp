/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Obstacle.h"
#include "GameScene1.h"
#include "Definitions.h"

USING_NS_CC;

Obstacle::Obstacle()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Obstacle::SpawnObstacle(cocos2d::Scene* scene)
{
	CCLOG("OBSTACLE SPAWN");

	auto obstacle = Sprite::create("Meteor.png");

	auto obstacleBody = PhysicsBody::createCircle(10);

	auto random = CCRANDOM_0_1();

	if (random < LOWER_GAP) 
	{
		random = LOWER_GAP;
	}
	else if (random > UPPER_GAP)
	{
		random = UPPER_GAP;
	}

	auto obstaclePosition = (random * visibleSize.height) + (obstacle->getContentSize().height / 2);

	obstacleBody->setDynamic(false);
	obstacleBody->setCollisionBitmask(OBSTACLE_COLLITION_BITMASK);
	obstacleBody->setContactTestBitmask(true);



	obstacle->setPhysicsBody(obstacleBody);

	obstacle->setPosition(Point(visibleSize.width + obstacle->getContentSize().width + origin.x, obstaclePosition));

	scene->addChild(obstacle);

	auto obstacleAction = MoveBy::create(0.009f * visibleSize.width, Point(-visibleSize.width * 1.5, 0));
	obstacle->runAction(obstacleAction);
}