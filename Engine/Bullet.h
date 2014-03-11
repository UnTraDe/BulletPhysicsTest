#pragma once
#include "Object.h"
#include "CommonData.h"

class Bullet : public Object
{
public:
	Bullet();
	~Bullet();

	void Update(float deltaTime);
	void Render(const glm::mat4 &projection, const glm::mat4 &view);

private:
	static const Vertex CubeVertices[];
	static GLuint mVao;
	static GLuint mVbo;

	//Physics
	static btCollisionShape* mShape;

	static int mInstanceCounter;
};

