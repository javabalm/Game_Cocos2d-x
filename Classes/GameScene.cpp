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

#include "GameScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "GameOver.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics( );
    scene->getPhysicsWorld( )->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_NONE );
    scene->getPhysicsWorld( )->setGravity( Vect( 0, 0 ) );
    
    auto layer = GameScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld( ) );
    
    scene->addChild(layer);
    
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto vSize = Director::getInstance()->getVisibleSize();
    auto vWidth = vSize.width;
    auto vHeight = vSize.height;
    
    auto backOrig = Sprite::create("res/imagenes/background.png");
    auto oWidth = backOrig->getContentSize().width;
    auto oHeight = backOrig->getContentSize().height;
    backOrig->setFlippedY( true );
    backOrig->setScale( vWidth / oWidth, (vHeight / oHeight)*2 );
    backOrig->setPosition( vWidth / 2, vHeight / 2 );
 
    addChild( backOrig );
    
    
    this->schedule(schedule_selector(GameScene::SpawnFish), FISH_SPAWN_FREQUENCY *visibleSize.width);
    
    fish = new Fish(this);
    
    auto contactListener = EventListenerPhysicsContact::create( );
    contactListener->onContactBegin = CC_CALLBACK_1( GameScene::onContactBegin, this );
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( contactListener, this );
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches( true );
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( touchListener, this );
    
    
    //score = 0;
    __String *tempScore = __String::createWithFormat( "%i", score );
    
    scoreLabel = Label::createWithTTF( tempScore->getCString( ), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE );
    scoreLabel->setColor( Color3B::WHITE );
    scoreLabel->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y ) );
    this->addChild( scoreLabel, 10000 );
    
    
    
    return true;
}

void GameScene::SpawnFish(float dt)
{
    badFish.SpawnFish(this);
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();
    
    if ( ( FISH2_COLLISION_BITMASK == a->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( FISH2_COLLISION_BITMASK == b->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
        score++;
        __String *tempScore = __String::createWithFormat( "%i", score );
        scoreLabel->setString( tempScore->getCString( ) );
        
        badFish.DeadBadFish();
    }
    else if(( FISH2_COLLISION_BITMASK == a->getCollisionBitmask( ) && FISH_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( FISH2_COLLISION_BITMASK == b->getCollisionBitmask( ) && FISH_COLLISION_BITMASK == a->getCollisionBitmask() ))
    {
        auto scene = GameOver::createScene( score );
        Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    }
    
    return true;
}



bool GameScene::onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *event)
{
    //CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
    fish -> updateAngle(touch->getLocation());
    
    if(badFish.ClickBadFish(touch->getLocation(), this) == true)
    {
        fish -> CambioImagen();
    }

    return true;
}


void GameScene::onTouchMoved( cocos2d::Touch *touch, cocos2d::Event *event)
{
    //fish -> Rotacion(touch);
    //CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
    fish -> updateAngle(touch->getLocation());
}

