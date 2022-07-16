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
	if (this->Light) {
		this->ColorTarget = this->Colors[((int)Position.x + (int)Position.y) % 2] * 2.0f;
	} else {
		this->ColorTarget = this->Colors[((int)Position.x + (int)Position.y) % 2] * 0.7f;
	}
	this->Color = glm::mix(this->Color, this->ColorTarget, glm::vec3(0.1f));
}

void Tile::Draw() {
	if (this->Visible)
		this->Sprite->Render(this->Position * this->Size + this->Size/2.0f, this->Size, 0.0f, this->Color);
}