#include "NPC.h"

#include "GameLoop.h"
#include "ResourceManager.h"

NPC::NPC(glm::vec2 pos, int index) : Position(pos) {
	Shader basicShader = ResourceManager::GetShader("basicShader");
	Texture tex, tex2;
	switch (index) {
	case 4:
		tex = ResourceManager::GetTexture("disco1");
		tex2 = ResourceManager::GetTexture("disco2");
		break;
	case 5:
		tex = ResourceManager::GetTexture("cup1");
		tex2 = ResourceManager::GetTexture("cup2");
		break;
	case 6:
		tex = ResourceManager::GetTexture("fries1");
		tex2 = ResourceManager::GetTexture("fries2");
		break;
	case 7:
		tex = ResourceManager::GetTexture("donut1");
		tex2 = ResourceManager::GetTexture("donut2");
		break;
	}
	this->Sprite1 = new SpriteObject(basicShader, tex);
	this->Sprite2 = new SpriteObject(basicShader, tex2);
}

NPC::~NPC() {
	delete this->Sprite1;
	delete this->Sprite2;
}

void NPC::Update(float deltaTime) {}

void NPC::Draw() {
	if ((int)(GameLoop::elapsedTime * 4.0) % 2 == 0)
		this->Sprite1->Render(this->Position * this->Size + glm::vec2(this->Size.x / 2.0f, 4.0f), this->Size);
	else
		this->Sprite2->Render(this->Position * this->Size + glm::vec2(this->Size.x / 2.0f, 4.0f), this->Size);
}