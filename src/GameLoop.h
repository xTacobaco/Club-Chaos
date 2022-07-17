#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Level.h"

#include <irrklang/irrKlang.h>
using namespace irrklang;

class GameLoop {
public:
    static double           elapsedTime;
    static bool             Keys[1024];
    unsigned int            Width, Height;

    bool pressed = false;
    static int state;
    SpriteObject* MenuSprite;
    SpriteObject* TutorialSprite;
    SpriteObject* EndSprite;

    static int currentLevel;
    static std::vector<Level*> levels;
    static ISoundEngine* SoundEngine;


    GameLoop(unsigned int width, unsigned int height) : Width(width), Height(height) {}
    ~GameLoop();
  
    void Init();
    void Update(float deltatime);
    void Render();
};
