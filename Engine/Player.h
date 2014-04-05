#pragma once

#include "Object.h"

class Player : public Object
{
public:
	Player();
	~Player();

	void Update(float deltaTime);
	void Render(const glm::mat4 &projection, const glm::mat4 &view, Shader* shader);
private:
	static btCollisionShape* mShape;
};

