#pragma once
#include <glm/ext.hpp>
#include <GL/glew.h>
#include "ResourceManager.h"
#include "CommonData.h"
#include <glm/glm.hpp>
#include <bullet/btBulletDynamicsCommon.h>

class Terrain
{
public:
	Terrain();
	~Terrain();
	void Render(const glm::mat4 &projection, const glm::mat4 &view);
	btRigidBody* GetRigidBody() { return mRigidBody; };
private:
	static const Vertex vertices[];
	GLuint mVao;
	GLuint mVbo;

	//Properties
	glm::vec3 mColor;

	btRigidBody* mRigidBody;
};

