#include "HelloWorldScene.h"
#include "cmath"

USING_NS_AX;


bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;


    playerSprite = ax::Sprite::create("playerSquare.png");

    // TO KEEP THIS LESSON SIMPLE, THE PIVOT IS AT 0, 0 (bottom, left)
    playerSprite->setAnchorPoint(ax::Vec2(0, 0));
  
    this->addChild(playerSprite, 10);


    // Creating the TileMap and accessing its data (tmx)
    tileMap = new ax::FastTMXTiledMap();
    tileMap->initWithTMXFile("tiled/tilesmap.tmx");
    this->addChild(tileMap);

    
    TMXObjectGroup* playerSpawnTMXObjGroup = tileMap->getObjectGroup("playerSpawnObjectLayer");
    auto spawnPointObject = playerSpawnTMXObjGroup->getObject("SpawnPoint_1");
    playerPosX = spawnPointObject.at("x").asFloat();
    playerPosY = spawnPointObject.at("y").asFloat();

    metaLayer = tileMap->getLayer("meta");
    //metaLayer->setVisible(false);


    // Create keyboard event listener to move sprite with WSAD (notice the '&' in the lambda closures)
    auto eventListenerKeyboard = EventListenerKeyboard::create();
    eventListenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* event)
    {
        keys[int(code)] = true;
    };
    eventListenerKeyboard->onKeyReleased = [&](EventKeyboard::KeyCode code, Event* event)
    {
        keys[int(code)] = false;

    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListenerKeyboard, playerSprite);


    playerSprite->setPosition(playerPosX, playerPosY);


    // Update
    scheduleUpdate();

    // Center the scene using the player position
    setViewPointCenter(playerSprite->getPosition());



    return true;
}




void HelloWorld::playerMove(float delta)
{
    // Inputs
    playerVelocityX = 300.f * keys[int(EventKeyboard::KeyCode::KEY_D)] + -300.f * keys[int(EventKeyboard::KeyCode::KEY_A)];
    playerVelocityY = 300.f * keys[int(EventKeyboard::KeyCode::KEY_W)] + -300.f * keys[int(EventKeyboard::KeyCode::KEY_S)];


    // Calculate potential new position
    float playerNextPosX = playerPosX + playerVelocityX * delta;
    float playerNextPosY = playerPosY + playerVelocityY * delta;



    playerPosX = playerNextPosX;
    playerPosY = playerNextPosY;
    playerSprite->setPosition(playerPosX, playerPosY);

   

}

Vec2 HelloWorld::getTiledMapSizeResolution()
{
    auto tileMapXRes = tileMap->getMapSize().width * 32;
    auto tileMapYRes = tileMap->getMapSize().height * 32;
    return Vec2(tileMapXRes, tileMapYRes);
}


void HelloWorld::setViewPointCenter(Vec2 position)
{
    auto visSize = Director::getInstance()->getVisibleSize();

    // Algorithm to keep the Scene position between the boundaries
    int x = MAX(position.x, visSize.width / 2);
    x = MIN(x, getTiledMapSizeResolution().x - visSize.width / 2);
    int y = MAX(position.y, visSize.height / 2);
    y = MIN(y, getTiledMapSizeResolution().y - visSize.height / 2);

    auto actualPosition = Vec2(x, y);
    auto centerOfView = Vec2(visSize.width / 2, visSize.height / 2);
    auto viewPoint = Vec2(centerOfView.x - actualPosition.x, centerOfView.y - actualPosition.y);

    setPosition(viewPoint);  // sets the position of the this, which is our Scene node
}



void HelloWorld::update(float delta)
{

    playerMove(delta);
    setViewPointCenter(Vec2(playerSprite->getPositionX(), 0));
}