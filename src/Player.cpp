#include "Player.h"

#include <cmath>

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
		int dx = (GameLoop::Keys[GLFW_KEY_D] || GameLoop::Keys[GLFW_KEY_RIGHT]) - (GameLoop::Keys[GLFW_KEY_A] || GameLoop::Keys[GLFW_KEY_LEFT]);
		int dy = (GameLoop::Keys[GLFW_KEY_S] || GameLoop::Keys[GLFW_KEY_DOWN]) - (GameLoop::Keys[GLFW_KEY_W] || GameLoop::Keys[GLFW_KEY_UP]);

		glm::vec2 dir = glm::vec2(dx, dy);
		glm::vec2 move = TargetPosition + dir;

		if ((dx != 0 || dy != 0) && released) {
			released = false;

			bool hit = false;
			auto time = std::fmod(GameLoop::elapsedTime * 2.0f, 16.0f);
			if (GameLoop::currentLevel == 0) {
				if (
					(time > 1.0f && time < 2.0f) ||
					(time > 3.0f && time < 4.0f) ||
					(time > 5.0f && time < 6.0f) ||
					(time > 7.0f && time < 8.0f) ||
					(time > 9.0f && time < 10.0f) ||
					(time > 11.0f && time < 12.0f) ||
					(time > 13.0f && time < 14.0f) ||
					(time > 15.0f && time < 16.0f)
					) {
					hit = true;
				}
			}
			else if (GameLoop::currentLevel == 1) {
				if (
					(time > 0.0f && time < 1.0f) ||
					(time > 2.0f && time < 3.0f) ||
					(time > 5.0f && time < 6.0f) ||
					(time > 6.0f && time < 7.0f) ||
					(time > 8.0f && time < 9.0f) ||
					(time > 10.0f && time < 11.0f) ||
					(time > 13.0f && time < 14.0f) ||
					(time > 14.0f && time < 15.0f)
					) {
					hit = true;
				}
			}

			if (hit && GameLoop::levels[GameLoop::currentLevel]->tiles[(int)move.y * 40 + (int)move.x]->isPath) {
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

				if (GameLoop::currentLevel == 0 && GameLoop::levels[GameLoop::currentLevel]->goal == TargetPosition) {
					GameLoop::currentLevel++;
					GameLoop::SoundEngine->setAllSoundsPaused();
					GameLoop::SoundEngine->play2D("res/levels/lvl2.mp3", true);
				}
				if (GameLoop::currentLevel == 0 && GameLoop::levels[GameLoop::currentLevel]->goal == TargetPosition) {
					GameLoop::currentLevel++;
				}
				if (GameLoop::currentLevel == 1 && GameLoop::levels[GameLoop::currentLevel]->goal == TargetPosition) {
					GameLoop::state = 3;
				}
				
				moved = 0.5 + GameLoop::elapsedTime;
			} else {
				// else screenshake + penelty
				moved = 1 + GameLoop::elapsedTime;
				damage = 1 + GameLoop::elapsedTime;
				GameLoop::SoundEngine->play2D("res/audio/ouch.mp3", false);
			}
		}
		if (dx == 0 && dy == 0) {
			released = true;
		}
	}
	Position = glm::mix(Position, TargetPosition, 0.1);
}

void Player::Draw() {
	glm::vec3 color = glm::vec3(1.0f);
	if (GameLoop::elapsedTime < damage) {
		color = glm::vec3(0.2f);
	}

	if ((int)(GameLoop::elapsedTime * 4.0) % 2 == 0)
		this->Sprite1->Render(this->Position * this->Size + glm::vec2(this->Size.x / 2.0f, 4.0f), this->Size, 0.0f, color);
	else
		this->Sprite2->Render(this->Position * this->Size + glm::vec2(this->Size.x / 2.0f, 4.0f), this->Size, 0.0f, color);
}