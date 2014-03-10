#pragma once

#include <bullet/btBulletDynamicsCommon.h>
#include "Object.h"
#include "CommonData.h"

#include <iostream>

class Cube : public Object
{
public:
	Cube(int size, btDiscreteDynamicsWorld* dynamicsWorld);
	~Cube();

	void Update(float deltaTime);
	void Render(const glm::mat4 &projection, const glm::mat4 &view);

private:
	static const Vertex CubeVertices[];
	static GLuint mVao;
	static GLuint mVbo;
	static int mInstanceCounter;

	btRigidBody* fallRigidBody;
};