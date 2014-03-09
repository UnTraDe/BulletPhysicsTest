#include "ResourceManager.h"

ResourceManager* ResourceManager::mInstance = nullptr;

void ResourceManager::CreateInstance()
{
	if (mInstance != nullptr)
	{
		//TODO Throw some exception
		return;
	}

	mInstance = new ResourceManager();
}

void ResourceManager::LoadTexture(const std::string &name)
{
	std::string path(TEXTURE_BASE_PATH);
	path.append(name);

	GLuint texture = SOIL_load_OGL_texture(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	if (!texture)
		std::cout << "Error loading texture: " << name << " Reason: " << SOIL_last_result() << std::endl;

	std::stringstream s(name);
	std::string keyName;
	std::getline(s, keyName, '.');

	mTextures[keyName] = texture;
}

void ResourceManager::LoadShader(const std::string &vertex, const std::string &fragment)
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