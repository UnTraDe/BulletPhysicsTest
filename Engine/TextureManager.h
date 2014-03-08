#pragma once


#include <string>
#include <sstream>
#include <hash_map>
#include <GL/glew.h>
#include <SOIL.h>

#include <iostream>

#define TEXTURE_BASE_PATH "resources/textures/"

class TextureManager
{
public:
	TextureManager() { };
	~TextureManager() { };

	void LoadTexture(const std::string &name);
	GLuint GetTexture(const std::string &name) { return mTextures[name]; };

private:
	std::hash_map<std::string, GLuint> mTextures;
};