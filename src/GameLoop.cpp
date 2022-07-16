#include "GameLoop.h"

#include <vector>

#include "Level.h"
#include "SpriteObject.h"
#include "ResourceManager.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;
ISoundEngine* SoundEngine = createIrrKlangDevice();

std::vector<Level*> levels;

double GameLoop::elapsedTime = 0;

GameLoop::~GameLoop() {
	for (auto level : levels) {
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

	levels.push_back(ResourceManager::LoadLevel("res/levels/lvl1"));

	SoundEngine->play2D("res/levels/lvl1.mp3", true);
}

void GameLoop::Update(float deltatime) {
	elapsedTime += (double) deltatime;
}

void GameLoop::Render() {
	glClearColor(0.13f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	levels[0]->Draw();
}