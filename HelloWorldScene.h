#pragma once
#include "axmol.h"
#include <vector>
#include <optional>
#include <string>

class HelloWorld : public ax::Scene
{

public:
    bool init() override;
    void update(float delta) override;
    void playerMove(float delta);

    ax::Vec2 getTiledMapSizeResolution();

    // Camera
    void setViewPointCenter(ax::Vec2 position);

    // Player attributes
    ax::Sprite* playerSprite;
    double playerPosX;
    double playerPosY;
    double playerVelocityX;
    double playerVelocityY;
   

    // Tile map attributes
    ax::FastTMXTiledMap* tileMap;
    ax::TMXLayer* metaLayer;

    // Keys
    bool keys[255] = { false };


};

