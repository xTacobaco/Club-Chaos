#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Level.h"

class GameLoop {
public:
    static double           elapsedTime;
    static bool             Keys[1024];
    unsigned int            Width, Height;
    
    static int currentLevel;
    static std::vector<Level*> levels;


    GameLoop(unsigned int width, unsigned int height) : Width(width), Height(height) {}
    ~GameLoop();
  
    void Init();
    void Update(float deltatime);
    void Render();
};
