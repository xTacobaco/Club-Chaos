#include "GameLoop.h"

#include <vector>

#include "SpriteObject.h"
#include "ResourceManager.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;
ISoundEngine* SoundEngine = createIrrKlangDevice();

int GameLoop::currentLevel = 0;
std::vector<Level*> GameLoop::levels;

double GameLoop::elapsedTime = 0;

GameLoop::~GameLoop() {
	for (auto level : GameLoop::levels) {
		delete level;
	}
}

void GameLoop::Init() {
	glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);

	ResourceManager::LoadShader("res/shaders/Basic.shader", "basicShader");
	Shader basicShader = ResourceManager::GetShader("basicShader").Bind();
	basicShader.SetInteger("image", 0);
	basicShader.SetMatrix4("projection", projection);

	ResourceManager::LoadTexture("res/textures/tile.png", true, "tile");
	
	ResourceManager::LoadTexture("res/textures/dit.png", true, "dit");
	ResourceManager::LoadTexture("res/textures/dash.png", true, "dash");
	ResourceManager::LoadTexture("res/textures/arrow.png", true, "arrow");
	
	ResourceManager::LoadTexture("res/textures/player.png", true, "player");
	ResourceManager::LoadTexture("res/textures/player2.png", true, "player2");
	
	ResourceManager::LoadTexture("res/textures/dice1.png", true, "dice1");
	ResourceManager::LoadTexture("res/textures/dice2.png", true, "dice2");
	ResourceManager::LoadTexture("res/textures/dice3.png", true, "dice3");
	ResourceManager::LoadTexture("res/textures/dice4.png", true, "dice4");
	ResourceManager::LoadTexture("res/textures/dice5.png", true, "dice5");
	ResourceManager::LoadTexture("res/textures/dice6.png", true, "dice6");
	
	ResourceManager::LoadTexture("res/textures/kid1.png", true, "kid1");
	ResourceManager::LoadTexture("res/textures/kid2.png", true, "kid2");

	levels.push_back(ResourceManager::LoadLevel("res/levels/lvl1"));

	SoundEngine->play2D("res/levels/lvl1.mp3", true);
	SoundEngine->setSoundVolume(0.3f);
}

void GameLoop::Update(float deltatime) {
	elapsedTime += (double) deltatime;

	levels[currentLevel]->Update(deltatime);
}

void GameLoop::Render() {
	glClearColor(0.13f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	levels[currentLevel]->Draw();
}