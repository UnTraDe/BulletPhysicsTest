#include "Object.h"

Object::Object()
{
	
}

Object::~Object()
{
	delete mMotionState;
	delete mRigidBody;
}

glm::vec3 Object::GetPosition()
{
	btTransform transform;
	mRigidBody->getMotionState()->getWorldTransform(transform);
	return glm::vec3(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ());
}

void Object::SetPosition(glm::vec3 position)
{
	btTransform transform;
	mRigidBody->getMotionState()->getWorldTransform(transform);
	mRigidBody->setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.x, position.y, position.z)));
}
