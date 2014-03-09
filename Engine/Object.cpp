#include "Object.h"
#include "CommonData.h"

Object::Object()
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);
}

Object::~Object()
{
	glDeleteBuffers(1, &mVbo);
	glDeleteVertexArrays(1, &mVao);
}