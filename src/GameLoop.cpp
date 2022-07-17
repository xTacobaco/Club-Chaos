#include "GameLoop.h"

#include <vector>
#include <iostream>

#include "SpriteObject.h"
#include "ResourceManager.h"

int GameLoop::state = 0;
int GameLoop::currentLevel = 0;
std::vector<Level*> GameLoop::levels;


ISoundEngine* GameLoop::SoundEngine = createIrrKlangDevice();
double GameLoop::elapsedTime = 0;

GameLoop::~GameLoop() {
	for (auto level : GameLoop::levels) {
		delete level;
	}
	delete MenuSprite;
	delete TutorialSprite;
	delete EndSprite;
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
	ResourceManager::LoadTexture("res/textures/line.png", true, "line");
	
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

	ResourceManager::LoadTexture("res/textures/disco1.png", true, "disco1");
	ResourceManager::LoadTexture("res/textures/disco2.png", true, "disco2");
	ResourceManager::LoadTexture("res/textures/cup1.png", true, "cup1");
	ResourceManager::LoadTexture("res/textures/cup2.png", true, "cup2");
	ResourceManager::LoadTexture("res/textures/fries1.png", true, "fries1");
	ResourceManager::LoadTexture("res/textures/fries2.png", true, "fries2");
	ResourceManager::LoadTexture("res/textures/donut1.png", true, "donut1");
	ResourceManager::LoadTexture("res/textures/donut2.png", true, "donut2");

	ResourceManager::LoadTexture("res/textures/menu.png", false, "menu");
	ResourceManager::LoadTexture("res/textures/tutorial.png", false, "tutorial");
	ResourceManager::LoadTexture("res/textures/end.png", false, "end");
	
	Texture menuTexture = ResourceManager::GetTexture("menu");
	MenuSprite = new SpriteObject(basicShader, menuTexture);

	Texture tutorialTexture = ResourceManager::GetTexture("tutorial");
	TutorialSprite = new SpriteObject(basicShader, tutorialTexture);

	Texture endTexture = ResourceManager::GetTexture("end");
	EndSprite = new SpriteObject(basicShader, endTexture);
	
	levels.push_back(ResourceManager::LoadLevel("res/levels/lvl1", 1));
	levels.push_back(ResourceManager::LoadLevel("res/levels/lvl2", 2));

	GameLoop::SoundEngine->play2D("res/levels/titlescreen.mp3", true);
	GameLoop::SoundEngine->setSoundVolume(0.3f);
}

void GameLoop::Update(float deltatime) {
	if (GameLoop::state == 0) {
		if (GameLoop::Keys[GLFW_KEY_SPACE]) {
			pressed = true;
			GameLoop::state = 1;
		}
	}
	if (GameLoop::state == 1) {
		if (! GameLoop::Keys[GLFW_KEY_SPACE]) {
			pressed = false;
		}
		if (! pressed && GameLoop::Keys[GLFW_KEY_SPACE]) {
			GameLoop::state = 2;
			GameLoop::SoundEngine->setAllSoundsPaused();
			GameLoop::SoundEngine->play2D("res/levels/lvl1.mp3", true);
		}
	}

	if (GameLoop::state == 2) {
		if (GameLoop::currentLevel == 0) {
			elapsedTime += (double) deltatime;
		}
		if (GameLoop::currentLevel == 1) {
			elapsedTime += (double)deltatime * 1.08f; // crazy game-jammy hack to match bpm of song
		}
		levels[currentLevel]->Update(deltatime);
	}
}

void GameLoop::Render() {
	glClearColor(0.13f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (GameLoop::state == 0) {
		glm::vec2 pos = glm::vec2(1280.0f, 720.0f);
		MenuSprite->Render(pos / 2.0f, pos);
	}
	if (GameLoop::state == 1) {
		glm::vec2 pos = glm::vec2(1280.0f, 720.0f);
		TutorialSprite->Render(pos / 2.0f, pos);
	}
	if (GameLoop::state == 2) {
		levels[currentLevel]->Draw();
	}
	if (GameLoop::state == 3) {
		glm::vec2 pos = glm::vec2(1280.0f, 720.0f);
		EndSprite->Render(pos / 2.0f, pos);
	}
}