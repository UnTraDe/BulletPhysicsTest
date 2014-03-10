#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include <bullet/btBulletDynamicsCommon.h>
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
	
	btRigidBody* GetRigidBody() { return mRigidBody; }


protected:
	glm::vec3 mPosition;
	std::vector<glm::vec3> mVertices;

	//- Physics -
	btDefaultMotionState* mMotionState;
	btRigidBody* mRigidBody;
};