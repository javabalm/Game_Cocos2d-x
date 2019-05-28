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

#include "BadFish.h"
#include "Definitions.h"

USING_NS_CC;

BadFish::BadFish()
{
    
    VisibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

void BadFish::SpawnFish(cocos2d::Layer *layer)
{
    
    auto vSize = Director::getInstance()->getVisibleSize();
    auto vWidth = vSize.width;
    auto vHeight = vSize.height;
    
    topFish = Sprite::create( "res/imagenes/badFish.png" );
    
    auto topFishBody = PhysicsBody::createBox( topFish->getContentSize( ) );
    
    auto oWidth = topFish->getContentSize().width;
    auto oHeight = topFish->getContentSize().height;
    
    topFish->setFlippedY( true );
    topFish->setScale( (vWidth / oWidth)*0.1, (vHeight / oHeight)*0.2 );
    
    auto random = CCRANDOM_MINUS1_1( );
    auto random2 = CCRANDOM_MINUS1_1( );
    
    topFishBody->setDynamic( false );
    topFishBody->setCollisionBitmask( FISH2_COLLISION_BITMASK );
    topFishBody->setContactTestBitmask( true );
    
    topFish->setPhysicsBody( topFishBody );

    
    if(pow(random,2) > pow(random2,2))
    {
        if(random > 0)
        {
            //CCLOG("1");
            auto HeightPosition = ( random * VisibleSize.height );
            topFish->setPosition( Point( VisibleSize.width, HeightPosition ));
            topFishAction = MoveBy::create( FISH_MOVEMENT_SPEED * VisibleSize.height, Point(-VisibleSize.width/2 + origin.x, VisibleSize.height/2 + origin.y - HeightPosition));
            topFish->runAction( topFishAction );

        }
        else
        {
            //CCLOG("2");
            random = random * (-1);
            auto HeightPosition = ( random * VisibleSize.height );
            topFish->setPosition( Point( 0, HeightPosition ));
            topFishAction = MoveBy::create( FISH_MOVEMENT_SPEED * VisibleSize.height, Point(VisibleSize.width/2 + origin.x, VisibleSize.height/2 + origin.y - HeightPosition));
            topFish->runAction( topFishAction );
        }
        
    }
    else
    {
        if(random > 0)
        {
            //CCLOG("3");
            auto WidthPosition = ( random * VisibleSize.width );
            topFish->setPosition( Point( WidthPosition, VisibleSize.height));
            topFishAction = MoveBy::create( FISH_MOVEMENT_SPEED * VisibleSize.height, Point(VisibleSize.width/2 + origin.x - WidthPosition, -VisibleSize.height/2 + origin.y));
            topFish->runAction( topFishAction );
        }
        else
        {
            //CCLOG("4");
            random = random * (-1);
            auto WidthPosition = ( random * VisibleSize.width );
            topFish->setPosition( Point( WidthPosition, 0 ));
            topFishAction = MoveBy::create( FISH_MOVEMENT_SPEED * VisibleSize.height, Point(VisibleSize.width/2 + origin.x - WidthPosition, VisibleSize.height/2 + origin.y));
            topFish->runAction( topFishAction );

        }
    }
    
    
    layer->addChild( topFish );
    firstFish = 1;
        
    
}

bool BadFish::ClickBadFish(cocos2d::Vec2 loc, cocos2d::Layer *layer)
{
    if(firstFish == 1)
    {
        if(topFish->getBoundingBox().containsPoint(loc))
        {
            
            auto vSize = Director::getInstance()->getVisibleSize();
            auto vWidth = vSize.width;
            auto vHeight = vSize.height;
            
            auto Bubble = Sprite::create( "res/imagenes/bubble.png" );
            
            auto BubbleBody = PhysicsBody::createBox( Bubble->getContentSize( ) );
            
            
            //fish.CambioImagen();
            
            auto oWidth = Bubble->getContentSize().width;
            auto oHeight = Bubble->getContentSize().height;
            
            BubbleBody->setDynamic( false );
            BubbleBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
            BubbleBody->setContactTestBitmask( true );
            
            Bubble->setPhysicsBody( BubbleBody );
            
            Bubble->setFlippedY( true );
            Bubble->setScale( (vWidth / oWidth)*0.05, (vHeight / oHeight)*0.1);
            
            layer->addChild(Bubble);
            
            Bubble->setPosition(Point(VisibleSize.width/2 + origin.x, VisibleSize.height/2 + origin.y));
            
            auto angle = atan2(loc.y - ((VisibleSize).height/2 + origin.y), loc.x - (VisibleSize.width/2 + origin.x));
            
            
            
            loc.y = VisibleSize.width * sin((-angle));
            loc.x = VisibleSize.width * cos((-angle));
            
            
            //CCLOG("X/2 = %f, Y/2 = %f, LOC.x = %f, loc.y = %f, angulo = %lf", VisibleSize.width/2 + origin.x, VisibleSize.height/2 + origin.y, loc.x, loc.y, CC_RADIANS_TO_DEGREES(-angle)+90);
            
            auto topFishAction = MoveBy::create( BUBBLE_MOVEMENT_SPEED * VisibleSize.height, Point(loc.x, -loc.y));
            
            Bubble->runAction( topFishAction );
            
            return true;
            
        }
    }
    
    return false;
    
}

void BadFish::DeadBadFish()
{

    topFish->stopAction(topFishAction);
    topFish->setPosition( Point( -100, -100 ));
}
