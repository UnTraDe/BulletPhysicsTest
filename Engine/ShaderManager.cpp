#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	
}

ShaderManager::~ShaderManager()
{
	for (std::hash_map<std::string, Shader*>::iterator it = mShaders.begin(); it != mShaders.end(); ++it)
	{
		//std::string key = it->first();
		//delete mShaders[key];
	}
}

void ShaderManager::LoadShader(const std::string &vertex, const std::string &fragment)
{
	std::string vert(SHADERS_BASE_PATH);
	vert.append(vertex);

	std::string frag(SHADERS_BASE_PATH);
	frag.append(fragment);

	Shader* shader = new Shader(vert.c_str(), frag.c_str());

	std::stringstream s(vertex);
	std::string keyName;
	std::getline(s, keyName, '.');

	mShaders[keyName] = shader;
}