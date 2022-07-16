#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "SpriteObject.h"

class Tile {
public:
    SpriteObject*   Sprite;
    glm::vec2       Position;
    bool            isPath = false;
    bool            Visible = false;
    glm::vec2       Size = glm::vec2(32.0f);
    glm::vec3       Color = glm::vec3(0.3f, 0.9f, 1.0f);

    Tile(glm::vec2 pos);
    ~Tile();

    virtual void Update(float deltaTime);
    virtual void Draw();
private:
};