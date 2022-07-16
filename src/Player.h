#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "SpriteObject.h"

class Player {
public:
    SpriteObject*   Sprite1;
    SpriteObject*   Sprite2;
    glm::vec2       Position;
    glm::vec2       TargetPosition;
    glm::vec2       Size = glm::vec2(32.0f);
    double          moved;
    
    Player(glm::vec2 pos);
    ~Player();

    virtual void Update(float deltaTime);
    virtual void Draw();
private:
};