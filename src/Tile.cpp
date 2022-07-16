#include "Tile.h"

#include "GameLoop.h"
#include "ResourceManager.h"

Tile::Tile(glm::vec2 pos) : Position(pos) {
	Shader basicShader = ResourceManager::GetShader("basicShader");
	Texture tex = ResourceManager::GetTexture("tile");
	this->Sprite = new SpriteObject(basicShader, tex);
}

Tile::~Tile() {
	delete this->Sprite;
}

void Tile::Update(float deltaTime) {
	if (! this->isPath) {
		auto math = ((float)glm::sin(GameLoop::elapsedTime*4) + 0.5f) / 2.0f;
		this->Color = glm::vec3(0.3f, 0.9f, 1.0f) * math;
	}
}

void Tile::Draw() {
	if (this->Visible)
		this->Sprite->Render(this->Position * this->Size + this->Size/2.0f, this->Size, 0.0f, this->Color);
}