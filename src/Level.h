#pragma once
#include <glad/glad.h>

#include "Tile.h"
#include "Dice.h"
#include "Player.h"
#include <vector>

class Level {
public:
    static const unsigned int tx = 40, ty = 23;
    Tile* tiles[tx * ty];
    std::vector<glm::vec2> path = { { 0, 11 }, { 1, 11 }, { 2, 11 }, { 3, 11 }, { 3, 10 }, { 4, 10 }, { 5, 10 }, { 5, 11 }, { 6, 11 }, { 7, 11 }, { 8, 11 } , { 9, 11 }, { 9, 10 }, { 9, 9 }, { 9, 8 }, { 9, 7 }, { 9, 6 }, { 10, 6 }, { 11, 6 }, { 11, 7 } };
    SpriteObject* lvlSprite;
    SpriteObject dit, dash;
    Player* player;
    Dice* dice;
    glm::vec2 spawn { 0.0f };
    
    Level(Texture lvlTexture);
    ~Level();
    
    void Draw();
    void Patherize();
    void Update(float deltatime);
};