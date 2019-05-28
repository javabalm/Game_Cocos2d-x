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

#include "Fish.h"
#include "Definitions.h"
#include "math.h"
#include "time.h"

USING_NS_CC;

Fish::Fish(cocos2d::Layer *layer)
{
    VisibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto vSize = Director::getInstance()->getVisibleSize();
    auto vWidth = vSize.width;
    auto vHeight = vSize.height;
    
    TheFish = Sprite::create("res/imagenes/fish.png");
    
    auto topFishBody = PhysicsBody::createBox( TheFish->getContentSize( ) );
        
    auto oWidth = TheFish->getContentSize().width;
    auto oHeight = TheFish->getContentSize().height;
    
    TheFish->setFlippedY( true );
    TheFish->setScale( (vWidth / oWidth)*0.1, (vHeight / oHeight)*0.2 );
    
    topFishBody->setDynamic( false );
    topFishBody->setCollisionBitmask( FISH_COLLISION_BITMASK );
    topFishBody->setContactTestBitmask( true );
    
    TheFish->setPhysicsBody( topFishBody );
    
    
    TheFish->setPosition(Point(VisibleSize.width/2 + origin.x, VisibleSize.height/2 + origin.y));
    
    layer->addChild(TheFish, 100);
    

}

void Fish::updateAngle(Vec2 loc)
{
    auto arrowWorldSpace = TheFish->getParent()->convertToWorldSpace(TheFish->getPosition());
    auto angle = atan2(loc.y - arrowWorldSpace.y, loc.x - arrowWorldSpace.x);
    
    /*auto rotate = RotateTo::create(SPEED_ROTATION, CC_RADIANS_TO_DEGREES(-angle) + 90);
    
    //auto callback = CallFunc::create(CC_CALLBACK_3(Fish::actionFinished,this));
    
    //auto callback = CC_CALLBACK_3(Fish::actionFinished, this);
    
    cocos2d::CallFunc* C = cocos2d::CallFunc::create([=]() {
        CCLOG("action completed!");
    });
    
    auto sequence = Sequence::create(rotate, C, NULL);
    TheFish->runAction(sequence);*/
    
    
    
    
    //TheFish->runAction(rotate);

    
    
    TheFish->setRotation(CC_RADIANS_TO_DEGREES(-angle) + 90);
    
   // CCLOG("x/2 = %f, y/2 = %f, loc.x = %f, loc.y = %f, angulo = %lf", arrowWorldSpace.x, arrowWorldSpace.y, loc.x, loc.y, CC_RADIANS_TO_DEGREES(-angle)+90);
}

void Fish::CambioImagen()
{
    auto oWidth = TheFish->getContentSize().width;
    auto oHeight = TheFish->getContentSize().height;
    
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(2);
    animFrames.pushBack(SpriteFrame::create("res/imagenes/fishBubble.png", Rect(0,0,oWidth, oHeight)));
    animFrames.pushBack(SpriteFrame::create("res/imagenes/fish.png", Rect(0,0,oWidth, oHeight)));

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Animate* animate = Animate::create(animation);
    
    TheFish->runAction(Repeat::create(animate, 1));
   
}

void Fish::actionFinished()
{
    CCLOG("action completed!");
}

