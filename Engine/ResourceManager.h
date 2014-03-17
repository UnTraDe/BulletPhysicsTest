#pragma once

#include <string>
#include <hash_map>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <SOIL.h>
#include "Shader.h"

#define TEXTURE_BASE_PATH "resources/textures/"
#define SHADERS_BASE_PATH "resources/shaders/"

class ResourceManager
{
public:
	void Initilize();
	void Unintialize();

	void LoadTexture(const std::string &name);
	void LoadTextureTransparent(const std::string &name);
	GLuint GetTexture(const std::string &name) { return mTextures[name]; };

	void LoadShader(const std::string &vertex, const std::string &geomtry, const std::string &fragment);
	Shader* GetShader(const std::string &name) { return mShaders[name]; };

	static ResourceManager* GetInstance() { return mInstance; };
	static void CreateInstance();

private:
	ResourceManager() { };

	std::hash_map<std::string, GLuint> mTextures;
	std::hash_map<std::string, Shader*> mShaders;

	static ResourceManager* mInstance;
};