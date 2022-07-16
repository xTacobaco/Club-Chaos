#include "Level.h"

#include <iostream>

#include "GameLoop.h"
#include "ResourceManager.h"

Level::Level(Texture lvlTexture) {
    Shader basicShader = ResourceManager::GetShader("basicShader").Bind();
    lvlSprite = new SpriteObject(basicShader, lvlTexture);

    Texture textureDit = ResourceManager::GetTexture("dit");
    Texture textureDash = ResourceManager::GetTexture("dash");
    dit = SpriteObject(basicShader, textureDit);
    dash = SpriteObject(basicShader, textureDash);

    player = new Player(spawn);
    dice = new Dice(glm::vec2(1280.0f/7.0f*5.0f, 48.0f));
}

void Level::Patherize() {
    for (auto p : path) {
        tiles[(int)p.y * 40 + (int)p.x]->Light = tiles[(int)p.y * 40 + (int)p.x]->isPath = true;
    }
}

Level::~Level() {
    for (auto t : tiles) { delete t; }
    delete lvlSprite;
    delete player;
    delete dice;
}

void Level::Update(float deltatime) {
    player->Update(deltatime);
    dice->Update(deltatime);

    for (auto t : tiles) {
        t->Light = (int)GameLoop::elapsedTime % 2;
    }

    for (auto p : path) {
        if (tiles[(int)p.y * 40 + (int)p.x]->isPath) {
            tiles[(int)p.y * 40 + (int)p.x]->Light = true;
        }
    }

    for (auto t : tiles) { t->Update(deltatime); }
}

void Level::Draw() {
    for (auto t : tiles) { t->Draw(); }

    glm::vec2 pos = glm::vec2(1280.0f, 720.0f);
    lvlSprite->Render(pos / 2.0f, pos);

    for (int i = 0; i < 16; i++) {
        glm::vec3 col = glm::vec3(0.5f);
        if ((int)((GameLoop::elapsedTime+15.5f) * 2.0f) % 16 == i) {
            col = glm::vec3(1.0f);
        }
        if (i % 2 != 0)
            dit.Render(glm::vec2(pos.x / 25.0f * (float)(i + 1), 48.0f), glm::vec2(48.0f), 0.0f, col);
        else
            dash.Render(glm::vec2(pos.x / 25.0f * (float)(i + 1), 48.0f), glm::vec2(48.0f), 0.0f, col);
    }

    player->Draw();
    dice->Draw();
}