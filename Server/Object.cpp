#include "Object.h"

ObjectState Object::GetObjectState()
{
	btTransform trans;
	m_RigidBody->getMotionState()->getWorldTransform(trans);
	btVector3 pos = trans.getOrigin();
	btVector3 lv = m_RigidBody->getLinearVelocity();
	btVector3 av = m_RigidBody->getAngularVelocity();
	btScalar rotation = trans.getRotation().getAngle();

	ObjectState os;
	os.id = m_Id;

	os.position[0] = pos.getX();
	os.position[1] = pos.getY();
	os.position[2] = pos.getZ();

	os.linearVelocity[0] = av.getX();
	os.linearVelocity[1] = av.getY();
	os.linearVelocity[2] = av.getZ();

	os.linearVelocity[0] = av.getX();
	os.linearVelocity[1] = av.getY();
	os.linearVelocity[2] = av.getZ();

	os.rotation = rotation;

	return os;
};