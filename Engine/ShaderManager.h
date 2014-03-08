#pragma once

#include <string>
#include <sstream>
#include <hash_map>
#include "Shader.h"

#define SHADERS_BASE_PATH "resources/shaders/"

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void LoadShader(const std::string &vertex, const std::string &fragment);
	Shader* GetShader(const std::string &name) { return mShaders[name]; };

private:
	std::hash_map<std::string, Shader*> mShaders;
};