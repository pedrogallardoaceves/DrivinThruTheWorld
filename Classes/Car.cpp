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

#include "Car.h"
#include "Definitions.h"
#include "GameScene1.h"

USING_NS_CC;

Car::Car(cocos2d::Scene *scene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	car = Sprite::create("CarroRosa.png");
	car->setPosition(Point((visibleSize.width / 2 + origin.x) - 80, (visibleSize.height / 2 + origin.y) - 95));
	
	auto carBody = PhysicsBody::createCircle(car->getContentSize().width / 5);
	carBody->setCollisionBitmask(CAR_COLLITION_BITMASK);
	carBody->setContactTestBitmask(true);
	carBody->setDynamic(false);

	car->setPhysicsBody(carBody);

	scene->addChild(car,100); 

}

void Car::Jump()
{
	auto action = JumpBy::create(1, Point(0, 0), 70, 1);
	car->runAction(action);
}
void Car::Stop()
{
	car->stopAllActions();
}
