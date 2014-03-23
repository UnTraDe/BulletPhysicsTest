#pragma once

#include "Object.h"

class Cube : public Object
{
public:
	Cube(int id, float position[3], float color[3]);
	~Cube();

	void Update(float deltaTime);

private:
	static btCollisionShape* m_Shape;
	static int m_InstanceCounter;
};