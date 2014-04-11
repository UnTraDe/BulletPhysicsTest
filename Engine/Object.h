#pragma once

#include <vector>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <bullet/btBulletDynamicsCommon.h>

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void Update(float deltaTime) = 0;
	virtual void Render(const glm::mat4 &projection, const glm::mat4 &view, Shader* shader) = 0;
	virtual bool IsAlive() { return true; }

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position);
	
	btRigidBody* GetRigidBody() { return mRigidBody; }

protected:
	std::vector<glm::vec3> mVertices;

	//- Physics -
	btDefaultMotionState* mMotionState;
	btRigidBody* mRigidBody;
};