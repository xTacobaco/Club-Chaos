#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "SpriteObject.h"

class Dice {
public:
    SpriteObject* Sprite1;
    SpriteObject* Sprite2;
    SpriteObject* Sprite3;
    SpriteObject* Sprite4;
    SpriteObject* Sprite5;
    SpriteObject* Sprite6;

    int side = 0;
    int offset = 0;
    glm::vec2 Position;
    float rotation = 0.0f;
    float target_rotation = 0.0f;
    glm::vec2 Size = glm::vec2(64.0f);
    
    Dice(glm::vec2 pos);
    ~Dice();

    virtual void Update(float deltaTime);
    virtual void Draw();
private:
};