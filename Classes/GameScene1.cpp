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

#include "GameScene1.h"
#include <cocostudio/SimpleAudioEngine.h>
#include "Car.h"
#include "Obstacle.h"
#include "DieScene.h"
#include "Definitions.h"
#include "GameScene2.h"

USING_NS_CC;

int points = 0;

Scene* GameScene1::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


	auto layer = GameScene1::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());


	scene->addChild(layer);

	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/GameScene_1.mp3");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	auto director = Director::getInstance();
	auto tamanio = director->getWinSize();

	auto Background = Sprite::create("MarioBackground.jpeg");
	Background->setAnchorPoint(Vec2::ZERO);
	Background->setPosition(Vec2::ZERO);
	this->addChild(Background, 0);
	auto moveBackground = MoveBy::create(30, Vec2(-970, 0));
	Background->runAction(moveBackground);

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/GameScene_1.mp3");

	this->schedule(CC_SCHEDULE_SELECTOR(GameScene1::SpawnObstacle), OBSTACLE_FREQUENCY * visibleSize.width);


	car=new Car (this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene1::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed=CC_CALLBACK_2(GameScene1::onKeyPressed,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);
	


	return true;
}

void GameScene1::SpawnObstacle(float dt)
{
	obstacle.SpawnObstacle(this);
	points++;
	st = std::to_string(points);
	auto label = Label::createWithTTF(st , "fonts/Marker Felt.ttf", 30);
	auto action = MoveBy::create(3, Vec2(-500, 0));
	label->setPosition(410, 300);
	label->setColor(Color3B::BLACK);
	label->enableOutline(Color4B::WHITE, .5);
	this->addChild(label, 100);
	label->runAction(action);
	if (points == 5)
	{
		auto scene = GameScene2::createScene();

		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}

}

bool GameScene1::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ((CAR_COLLITION_BITMASK == a->getCollisionBitmask() || OBSTACLE_COLLITION_BITMASK == b->getCollisionBitmask())|| (CAR_COLLITION_BITMASK == b->getCollisionBitmask() || OBSTACLE_COLLITION_BITMASK == a->getCollisionBitmask()))
	{
		auto scene = DieScene::createScene();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

	}
	return true;
}
void GameScene1::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
	if (key == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		car->Jump();
	}
}
void GameScene1::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{
	car->Stop();
}