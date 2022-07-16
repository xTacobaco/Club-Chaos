#include "Dice.h"

#include <iostream>

#include "Gameloop.h"
#include "ResourceManager.h"

Dice::Dice(glm::vec2 pos) : Position(pos) {
	Shader basicShader = ResourceManager::GetShader("basicShader");
	Texture tex = ResourceManager::GetTexture("dice1");		// lel, should have added spritesheets to my engine :D
	Texture tex2 = ResourceManager::GetTexture("dice2");	// this is incredibly resource wasteful :P
	Texture tex3 = ResourceManager::GetTexture("dice3");
	Texture tex4 = ResourceManager::GetTexture("dice4");
	Texture tex5 = ResourceManager::GetTexture("dice5");
	Texture tex6 = ResourceManager::GetTexture("dice6");
	this->Sprite1 = new SpriteObject(basicShader, tex);
	this->Sprite2 = new SpriteObject(basicShader, tex2);
	this->Sprite3 = new SpriteObject(basicShader, tex3);
	this->Sprite4 = new SpriteObject(basicShader, tex4);
	this->Sprite5 = new SpriteObject(basicShader, tex5);
	this->Sprite6 = new SpriteObject(basicShader, tex6);
}

Dice::~Dice() {
	delete this->Sprite1; 
	delete this->Sprite2;
 	delete this->Sprite3;
	delete this->Sprite4;
	delete this->Sprite5;
	delete this->Sprite6;
}

void Dice::Update(float deltaTime) {
	if ((int)GameLoop::elapsedTime % 8 == 0 &&  target_rotation - rotation < 1.0f) {
		target_rotation += 360.0f;
		offset = rand() % 6;
	}

	if (target_rotation - rotation > 1.0f) {
		side = (offset + (int)(GameLoop::elapsedTime * 8.0)) % 6;
	}

	rotation = glm::mix(rotation, target_rotation, 0.02f);
}

void Dice::Draw() {

	switch (side) {
		case 0:
			this->Sprite1->Render(this->Position, this->Size, this->rotation);
			break;
		case 1:
			this->Sprite2->Render(this->Position, this->Size, this->rotation);
			break;
		case 2:
			this->Sprite3->Render(this->Position, this->Size, this->rotation);
			break;
		case 3:
			this->Sprite4->Render(this->Position, this->Size, this->rotation);
			break;
		case 4:
			this->Sprite5->Render(this->Position, this->Size, this->rotation);
			break;
		case 5:
			this->Sprite6->Render(this->Position, this->Size, this->rotation);
			break;
	}

}