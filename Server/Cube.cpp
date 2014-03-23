#include "Cube.h"

int Cube::m_InstanceCounter = 0;
btCollisionShape* Cube::m_Shape = nullptr;

Cube::Cube(int id, float position[3], float color[3]) : Object(id)
{
	if (m_InstanceCounter == 0)
	{
		m_Shape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
	}

	m_MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position[0], position[1], position[2])));

	btScalar mass = 5;
	btVector3 inertia(0, 0, 0);
	m_Shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, m_MotionState, m_Shape, inertia);
	m_RigidBody = new btRigidBody(rigidBodyCI);
	m_RigidBody->setFriction(5.0);
	
	m_InstanceCounter++;
}

Cube::~Cube()
{
	m_InstanceCounter--;

	if (m_InstanceCounter == 0)
	{
		delete m_Shape;
	}
}

void Cube::Update(float deltaTime)
{

}