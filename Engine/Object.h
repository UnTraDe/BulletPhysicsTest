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
	virtual void Render(const glm::mat4 &projection, const glm::mat4 &view) = 0;

	glm::vec3 GetPosition();// { return glm::vec3(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ()); };
	void SetPosition(glm::vec3 position);// { mRigidBody->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.x, position.y, position.z))); };
	
	btRigidBody* GetRigidBody() { return mRigidBody; }


protected:
	std::vector<glm::vec3> mVertices;

	//- Physics -
	btDefaultMotionState* mMotionState;
	btRigidBody* mRigidBody;
};