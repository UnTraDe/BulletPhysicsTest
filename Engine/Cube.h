#pragma once

#include "Object.h"
#include "CommonData.h"


class Cube : public Object
{
public:
	Cube(glm::vec3 color);
	~Cube();

	void Update(float deltaTime);
	void Render(const glm::mat4 &projection, const glm::mat4 &view, Shader* shader);

private:
	static const Vertex CubeVertices[];
	static GLuint mVao;
	static GLuint mVbo;

	//Properties
	glm::vec3 mColor;

	//Physics
	static btCollisionShape* mShape;

	static int mInstanceCounter;
};