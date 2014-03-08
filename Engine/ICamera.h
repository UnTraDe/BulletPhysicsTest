#pragma once

#include <glm/glm.hpp>

class ICamera
{
public:
	virtual glm::mat4 GetView() = 0;
};