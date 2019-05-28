#include "GameOver.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int score;

Scene* GameOver::createScene( unsigned int tempScore )
{
    score = tempScore;
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->scheduleOnce(schedule_selector(GameOver::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);
    
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
    
    
    __String *tempScore = __String::createWithFormat( "Game Over - Score: %i", score );
    
    auto scoreLabel = Label::createWithTTF( tempScore->getCString( ), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE_GAME_OVER );
    scoreLabel->setColor( Color3B::WHITE );
    scoreLabel->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y ) );
    this->addChild( scoreLabel, 10000 );
    
    
    
    return true;
}

void GameOver::GoToMainMenuScene( float dt )
{
    auto scene = MainMenuScene::createScene( );
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}
