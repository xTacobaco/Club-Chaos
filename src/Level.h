#pragma once
#include <glad/glad.h>

#include "Tile.h"

class Level {
public:
    static const unsigned int tx = 40, ty = 23;
    Tile* tiles[tx * ty];
    SpriteObject* lvlSprite;

    Level(Texture lvlTexture);
    ~Level();

    void Draw();
};