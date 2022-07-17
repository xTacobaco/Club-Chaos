#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "stb_image/stb_image.h"

std::map<std::string, Texture>  ResourceManager::Textures;
std::map<std::string, Shader>   ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char* file, std::string name) {
    Shaders[name] = loadShaderFromFile(file);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name) {
    return Shaders[name];
}

Texture ResourceManager::LoadTexture(const char* file, bool alpha, std::string name) {
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name) {
    return Textures[name];
}

Level* ResourceManager::LoadLevel(const char* file) {
    return loadLevelFromFile(file);
}

void ResourceManager::Clear() {
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);

    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* file) {
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    std::string line;
    std::stringstream stringStream[3];
    ShaderType type = ShaderType::NONE;

    try {
        std::ifstream stream(file);

        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
            }
            else {
                stringStream[(int)type] << line << '\n';
            }
        }
    }
    catch (std::exception e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    std::string vertexCode = stringStream[(int)ShaderType::VERTEX].str();
    std::string fragmentCode = stringStream[(int)ShaderType::FRAGMENT].str();
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);
    return shader;
}

Texture ResourceManager::loadTextureFromFile(const char* file, bool alpha) {
    Texture texture;

    if (alpha) {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    texture.Generate(width, height, data);
    stbi_image_free(data);
    return texture;
}

Level* ResourceManager::loadLevelFromFile(const char* file) {
    std::string image_path(file);
    image_path.append(".png");
    ResourceManager::LoadTexture(image_path.c_str(), true, file);
    Texture lvlTexture = ResourceManager::GetTexture(file);
    
    std::string level_path(file);
    level_path.append(".level");

    std::ifstream stream(level_path);
    std::string line;
    unsigned int yy = 0;

    Level* level = new Level(lvlTexture);
    while (getline(stream, line)) {
        int width = line.length();
        for (int i = 0; i < width; i++) {
            Tile* tile = new Tile(glm::vec2(i, yy));
            if (line[i] == '0' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7') {
                tile->Visible = true;
            }
            if (line[i] == '2') {
                level->spawn = glm::vec2(i, yy);
                level->player->Position = level->spawn;
                level->player->TargetPosition = level->spawn;
            }
            if (line[i] == '3') {
                level->goal = glm::vec2(i, yy);
            }

            if (line[i] == '4') { level->npc[0] = new NPC(glm::vec2(i % width, yy), 4); }
            if (line[i] == '5') { level->npc[1] = new NPC(glm::vec2(i % width, yy), 5); }
            if (line[i] == '6') { level->npc[2] = new NPC(glm::vec2(i % width, yy), 6); }
            if (line[i] == '7') { level->npc[3] = new NPC(glm::vec2(i % width, yy), 7); }

            if (yy <= 3) {
                tile->Visible = false;
            }
            level->tiles[yy * width + i % width] = tile;
        }
        yy++;
    }
    level->Patherize();

    return level;
}