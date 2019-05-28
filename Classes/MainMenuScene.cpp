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

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene ::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto vSize = Director::getInstance()->getVisibleSize();
    auto vWidth = vSize.width;
    auto vHeight = vSize.height;
    
    auto backOrig = Sprite::create( "res/imagenes/menuBackground.png" );
    auto oWidth = backOrig->getContentSize().width;
    auto oHeight = backOrig->getContentSize().height;
    backOrig->setFlippedY( true );
    backOrig->setScale( vWidth / oWidth, vHeight / oHeight );
    backOrig->setPosition( vWidth / 2, vHeight / 2 );
    
    auto renderTexture = RenderTexture::create( vWidth, vHeight, Texture2D::PixelFormat::RGBA8888 );
    renderTexture->begin();
    backOrig->visit();
    renderTexture->end();
    
    auto backOk = Sprite::createWithTexture( renderTexture->getSprite()->getTexture() );
    backOk->setPosition( vWidth / 2, vHeight / 2 );
    addChild( backOk );

    
    
    auto label = Label::createWithTTF("Click the botton to start", "fonts/Marker Felt.ttf", 22);
    label -> setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height + origin.y - label->getContentSize().height));
    this -> addChild(label,1);
    
    
    auto playItem = MenuItemImage::create("res/imagenes/buttonRed.png", "res/imagenes/buttonRedPressed.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    
    playItem->setScale( 5, 3 );
    playItem->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref *sender)
{
    auto scene = GameScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
