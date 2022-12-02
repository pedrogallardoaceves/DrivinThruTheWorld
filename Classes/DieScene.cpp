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

#include "DieScene.h"
#include "GameScene1.h"
#include <cocostudio/SimpleAudioEngine.h>
#include "GameScene2.h"
USING_NS_CC;

Scene* DieScene::createScene()
{
    return DieScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool DieScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/FartToot.mp3");

    auto label = Label::createWithTTF("GAME OVER", "fonts/Marker Felt.ttf", 30);
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, (origin.y + visibleSize.height / 2) + 120));
    label->setColor(Color3B::WHITE);
    label->enableOutline(Color4B::WHITE, .5);
    this->addChild(label, 1);

    auto label2 = Label::createWithTTF("better luck the next time", "fonts/Marker Felt.ttf", 15);
    label2->setPosition(Vec2(origin.x + visibleSize.width / 2, (origin.y + visibleSize.height / 2) - 120));
    label2->setColor(Color3B::WHITE);
    label2->enableOutline(Color4B::RED, .8);
    this->addChild(label2, 1);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/FartToot.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/FartToot.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/FartToot.mp3");

    return true;
}
