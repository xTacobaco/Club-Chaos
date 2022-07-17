#include "Level.h"

#include <iostream>

#include "GameLoop.h"
#include "ResourceManager.h"

Level::Level(Texture lvlTexture) {
    Shader basicShader = ResourceManager::GetShader("basicShader").Bind();
    lvlSprite = new SpriteObject(basicShader, lvlTexture);

    Texture textureDit = ResourceManager::GetTexture("dit");
    Texture textureDash = ResourceManager::GetTexture("dash");
    Texture textureArrow = ResourceManager::GetTexture("arrow");
    dit = SpriteObject(basicShader, textureDit);
    dash = SpriteObject(basicShader, textureDash);
    arrow = SpriteObject(basicShader, textureArrow);

    Texture textureKid1 = ResourceManager::GetTexture("kid1");
    Texture textureKid2 = ResourceManager::GetTexture("kid2");
    profile1 = SpriteObject(basicShader, textureKid1);
    profile2 = SpriteObject(basicShader, textureKid2);

    player = new Player(spawn);
    dice = new Dice(glm::vec2(1280.0f/10.0f*8.0f, 64.0f));

    pp.push_back(path);
    pp.push_back(path2);
}

void Level::Patherize() { // jeeeeesus, should have just implemented A*
    for (auto t : tiles) {
        t->isPath = false;
    }

    for (auto p : pp[currentPath]) {
        tiles[(int)p.y * 40 + (int)p.x]->isPath = true;
    }

    int x = 9;
    for (int i = 0; i < 8; i++) {
        glm::vec2 pos = player->TargetPosition;
        int index = (int)pos.y * 40 + (int)pos.x + i;
        if (index < 0 || index > 40 * 23) { break; }
        if (!tiles[index]->Visible || tiles[index]->NPC != 0) { break; }
        if (tiles[index]->isPath)
            if (glm::abs(i) < glm::abs(x)) { x = i; break; }
    }
    for (int i = -1; i > -8; i--) {
        glm::vec2 pos = player->TargetPosition;
        int index = (int)pos.y * 40 + (int)pos.x + i;
        if (index < 0 || index > 40 * 23) { break; }
        if (!tiles[index]->Visible || tiles[index]->NPC != 0) { break; }
        if (tiles[index]->isPath)
            if (glm::abs(i) < glm::abs(x)) { x = i; break; }
    }
    int y = 9;
    for (int i = 0; i < 8; i++) {
        glm::vec2 pos = player->TargetPosition;
        int index = ((int)pos.y + i) * 40 + (int)pos.x;
        if (index < 0 || index > 40 * 23) { break; }
        if (!tiles[index]->Visible || tiles[index]->NPC != 0) { break; }
        if (tiles[index]->isPath)
            if (glm::abs(i) < glm::abs(x)) { y = i; break; }
    }
    for (int i = -1; i > -8; i--) {
        glm::vec2 pos = player->TargetPosition;
        int index = ((int)pos.y + i) * 40 + (int)pos.x;
        if (index < 0 || index > 40 * 23) { break; }
        if (!tiles[index]->Visible || tiles[index]->NPC != 0) { break; }
        if (tiles[index]->isPath)
            if (glm::abs(i) < glm::abs(y)) { y = i; break; }
    }

    glm::vec2 pos = player->TargetPosition;
    if (glm::abs(x) < glm::abs(y)) {
        pos.x += x;
        for (int i = 0; i < glm::abs(x); i++) {
            tiles[(int)player->TargetPosition.y * 40 + ((int)player->TargetPosition.x + i*glm::sign(x))]->isPath = true;
        }
    } else {
        pos.y += y;
        for (int i = 0; i < glm::abs(y); i++) {
            tiles[((int)player->TargetPosition.y + i * glm::sign(y)) * 40 + (int)player->TargetPosition.x]->isPath = true;
        }
    }
    
    for (auto p : pp[currentPath]) {
        if (glm::vec2(p.x, p.y) == pos) {
            break;
        }
        tiles[(int)p.y * 40 + (int)p.x]->isPath = false;
    }
    
    tiles[(int)player->TargetPosition.y * 40 + (int)player->TargetPosition.x]->isPath = true;

    for (auto t : tiles) {
        if (t->isPath) {
            t->glow = 10.0f;
        }
    }
    currentPath = ++currentPath % pp.size();
}

Level::~Level() {
    for (auto t : tiles) { delete t; }
    for (auto n : npc) { delete n; }
    delete lvlSprite;
    delete player;
    delete dice;
}

void Level::Update(float deltatime) {
    if ((int)GameLoop::elapsedTime % 8 == 0 && lastPatherized < (int)GameLoop::elapsedTime) {
        Patherize();
        lastPatherized = (int)GameLoop::elapsedTime + 1;
    }

    player->Update(deltatime);
    dice->Update(deltatime);

    for (auto t : tiles) {
        t->Light = (int)GameLoop::elapsedTime % 2;
    
        if (t->isPath) {
            t->Light = true;
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
            dit.Render(glm::vec2(120.0f + pos.x / 25.0f * (float)(i + 1), 64.0f), glm::vec2(48.0f), 0.0f, col);
        else
            dash.Render(glm::vec2(120.0f + pos.x / 25.0f * (float)(i + 1), 64.0f), glm::vec2(48.0f), 0.0f, col);
    }
    int index = (int)((GameLoop::elapsedTime + 15.5f) * 2.0f) % 16;
    arrowX = glm::mix(arrowX, 120.0f + pos.x / 25.0f * (float)(index + 1), 0.1f);
    arrow.Render(glm::vec2(arrowX, 128.0f), glm::vec2(48.0f));

    if ((int)(GameLoop::elapsedTime * 4.0) % 2 == 0)
        profile1.Render(glm::vec2(64.0f), glm::vec2(128.0f));
    else
        profile2.Render(glm::vec2(64.0f), glm::vec2(128.0f));
    
    for (auto n : npc) {
        n->Draw();
    }

    player->Draw();
    dice->Draw();
}