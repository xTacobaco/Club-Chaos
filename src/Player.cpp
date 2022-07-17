#include "Player.h"

#include <iostream>

#include "Gameloop.h"
#include "ResourceManager.h"

Player::Player(glm::vec2 pos) : Position(pos) {
	Shader basicShader = ResourceManager::GetShader("basicShader");
	Texture tex = ResourceManager::GetTexture("player");
	Texture tex2 = ResourceManager::GetTexture("player2");
	this->Sprite1 = new SpriteObject(basicShader, tex);
	this->Sprite2 = new SpriteObject(basicShader, tex2);
}

Player::~Player() {
	delete this->Sprite1;
	delete this->Sprite2;
}

void Player::Update(float deltaTime) {
	if (GameLoop::elapsedTime > moved) {
		int dx = GameLoop::Keys[GLFW_KEY_D] - GameLoop::Keys[GLFW_KEY_A];
		int dy = GameLoop::Keys[GLFW_KEY_S] - GameLoop::Keys[GLFW_KEY_W];
		
		glm::vec2 dir = glm::vec2(dx, dy);
		glm::vec2 move = TargetPosition + dir;

		if (dx != 0 || dy != 0) {
			if (GameLoop::levels[GameLoop::currentLevel]->tiles[(int)move.y * 40 + (int)move.x]->isPath) {
				GameLoop::levels[GameLoop::currentLevel]->tiles[(int)TargetPosition.y * 40 + (int)TargetPosition.x]->isPath = false;
				TargetPosition += dir;
				if (GameLoop::levels[GameLoop::currentLevel]->tiles[(int)TargetPosition.y * 40 + ((int)TargetPosition.x + 1)]->NPC != 0) {
					GameLoop::levels[GameLoop::currentLevel]->tiles[(int)TargetPosition.y * 40 + ((int)TargetPosition.x + 1)]->npcActive = true;
				}
				if (GameLoop::levels[GameLoop::currentLevel]->tiles[(int)TargetPosition.y * 40 + ((int)TargetPosition.x - 1)]->NPC != 0) {
					GameLoop::levels[GameLoop::currentLevel]->tiles[(int)TargetPosition.y * 40 + ((int)TargetPosition.x - 1)]->npcActive = true;
				}
				if (GameLoop::levels[GameLoop::currentLevel]->tiles[((int)TargetPosition.y + 1) * 40 + (int)TargetPosition.x]->NPC != 0) {
					GameLoop::levels[GameLoop::currentLevel]->tiles[((int)TargetPosition.y + 1) * 40 + (int)TargetPosition.x]->npcActive = true;
				}
				if (GameLoop::levels[GameLoop::currentLevel]->tiles[((int)TargetPosition.y - 1) * 40 + (int)TargetPosition.x]->NPC != 0) {
					GameLoop::levels[GameLoop::currentLevel]->tiles[((int)TargetPosition.y - 1) * 40 + (int)TargetPosition.x]->npcActive = true;
				}
				
				moved = 0.5 + GameLoop::elapsedTime;
			} else {
				// else screenshake + penelty
				moved = 1 + GameLoop::elapsedTime;
			}
		}
	}
	Position = glm::mix(Position, TargetPosition, 0.1);
}

void Player::Draw() {
	if ((int)(GameLoop::elapsedTime * 4.0) % 2 == 0)
		this->Sprite1->Render(this->Position * this->Size + glm::vec2(this->Size.x / 2.0f, 4.0f), this->Size);
	else
		this->Sprite2->Render(this->Position * this->Size + glm::vec2(this->Size.x / 2.0f, 4.0f), this->Size);
}