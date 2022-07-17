#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "SpriteObject.h"

class Tile {
public:
    SpriteObject*   Sprite;
    glm::vec2       Position;
    bool            Light = false;
    bool            isPath = false;
    bool            Visible = false;
    bool            npcActive = false;
    int             NPC = 0;
    float           glow = 0.0f;
    glm::vec2       Size = glm::vec2(32.0f);
    glm::vec3       Color = glm::vec3(0.3f, 0.9f, 1.0f);
    glm::vec3       ColorTarget = glm::vec3(0.3f, 0.9f, 1.0f);
    glm::vec3 Colors[3] = { glm::vec3(0.42f, 0.92f, 0.84f), glm::vec3(0.34f, 0.23f, 0.41f) * 1.5f };

    Tile(glm::vec2 pos);
    ~Tile();

    virtual void Update(float deltaTime);
    virtual void Draw();
private:
};