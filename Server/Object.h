#pragma once

#include <vector>
#include <bullet/btBulletDynamicsCommon.h>
#include "Structures.h"

class Object
{
public:
	Object(int id) : m_Id(id) {};
	virtual ~Object() {};

	virtual void Update(float deltaTime) = 0;
	virtual bool IsAlive() { return true; }
	btRigidBody* GetRigidBody() { return m_RigidBody; }

	ObjectState GetObjectState();

protected:
	int m_Id;
	btDefaultMotionState* m_MotionState;
	btRigidBody* m_RigidBody;
};