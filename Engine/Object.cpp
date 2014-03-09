#include "Object.h"
#include "CommonData.h"

Object::Object(Shader* shader)
{
	mShader = shader;

	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);
}

Object::~Object()
{
	glDeleteBuffers(1, &mVbo);
	glDeleteVertexArrays(1, &mVao);
}