#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "SpriteObject.h"

class NPC {
public:
    SpriteObject* Sprite1;
    SpriteObject* Sprite2;

    glm::vec2       Position;
    int             index = 0;
    glm::vec2       Size = glm::vec2(32.0f);
    glm::vec3       Color = glm::vec3(0.3f, 0.9f, 1.0f);

    NPC(glm::vec2 pos, int index);
    ~NPC();

    virtual void Update(float deltaTime);
    virtual void Draw();
private:
};