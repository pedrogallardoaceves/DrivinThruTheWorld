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

#include "WinScene.h"
#include <cocostudio/SimpleAudioEngine.h>
#include "GameScene4.h"
#include "Definitions.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* WinScene::createScene()
{
    return WinScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool WinScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/Winner.mp3");

    auto sprite = Sprite::create("WINNER.jpeg");
    sprite->setAnchorPoint(Vec2::ZERO);
    sprite->setPosition(Vec2::ZERO);
    this->addChild(sprite, 0);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/Winner.mp3");


    auto listenerKeyboard = EventListenerKeyboard().create();
    listenerKeyboard->onKeyPressed = CC_CALLBACK_2(WinScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

    return true;
}
void WinScene::GoToGameScene()
{
    auto scene = MenuScene::createScene();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void WinScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event)
{

    if (key == EventKeyboard::KeyCode::KEY_SPACE) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
        this->GoToGameScene();
    }
}