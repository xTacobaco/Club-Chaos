#include "Level.h"

#include "ResourceManager.h"

Level::Level(Texture lvlTexture) {
    Shader basicShader = ResourceManager::GetShader("basicShader").Bind();
    lvlSprite = new SpriteObject(basicShader, lvlTexture);
}

Level::~Level() {
    for (auto t : tiles) { delete t; }
    delete lvlSprite;
}

void Level::Draw() {
    for (auto t : tiles) { t->Draw(); }

    glm::vec2 pos = glm::vec2(1280.0f, 720.0f);
    lvlSprite->Render(pos / 2.0f, pos);
}