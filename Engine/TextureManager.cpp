#include "TextureManager.h"

void TextureManager::LoadTexture(const std::string &name)
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