#pragma once

#include "Object.h"
#include "CommonData.h"

class Cube : public Object
{
public:
	Cube(int size);
	~Cube();

	void Update(float deltaTime);
	void Render(const glm::mat4 &projection, const glm::mat4 &view);

private:
	static const Vertex CubeVertices[];
	static GLuint mVao;
	static GLuint mVbo;
	static int mInstanceCounter;

	float angle;
};