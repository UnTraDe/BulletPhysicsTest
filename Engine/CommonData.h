#pragma once

#include <glm/glm.hpp>

struct SimpleVertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

struct SimpleTexturedVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};
