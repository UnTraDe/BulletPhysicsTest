#pragma once

#include "Object.h"

class Cube : public Object
{
public:
	Cube(Shader* shader, int size);
	~Cube();

	void Update(float deltaTime);
	void Render(const glm::mat4 &projection, const glm::mat4 &view);

private:
	static const glm::vec3 CubeVertices[];

	float angle;
};