#pragma once

#include <string>
#include <hash_map>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <SOIL.h>
#include "Shader.h"
#include "HeightMap.h"


#define TEXTURE_BASE_PATH "resources/textures/"
#define SHADERS_BASE_PATH "resources/shaders/"
#define HEIGHTMAPS_BASE_PATH "resources/maps/"

class ResourceManager
{
public:
	void Initilize();
	void Unintialize();

	void LoadTexture(const std::string &name);
	GLuint GetTexture(const std::string &name) { return mTextures[name]; };

	void LoadShader(const std::string &vertex, const std::string &fragment);
	Shader* GetShader(const std::string &name) { return mShaders[name]; };

	void LoadHeightmap(const std::string &name);
	HeightMap* GetHeightmap(const std::string &name) { return mHeightMaps[name]; };

	static ResourceManager* GetInstance() { return mInstance; };
	static void CreateInstance();

private:
	ResourceManager() { };

	std::hash_map<std::string, GLuint> mTextures;
	std::hash_map<std::string, Shader*> mShaders;
	std::hash_map<std::string, HeightMap*> mHeightMaps;

	static ResourceManager* mInstance;
};