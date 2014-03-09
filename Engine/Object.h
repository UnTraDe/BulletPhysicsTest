#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include "ResourceManager.h"

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Update(float deltaTime) = 0;
	virtual void Render(const glm::mat4 &projection, const glm::mat4 &view) = 0;

	glm::vec3 GetPosition() { return mPosition; };
	void SetPosition(glm::vec3 position) { mPosition = position; };
	std::vector<glm::vec3>* GetVertices() { return &mVertices; };
	glm::mat4 GetModelMatrix() { return mModel; };

protected:
	glm::vec3 mPosition;
	std::vector<glm::vec3> mVertices;
	glm::mat4 mModel;
};