#include "Player.h"

btCollisionShape* Player::mShape = nullptr;

Player::Player()
{
	mShape = new btCapsuleShape(1.0, 2.0);
	mMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));

	btScalar mass = 5;
	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, mMotionState, mShape, inertia);
	mRigidBody = new btRigidBody(rigidBodyCI);
	mRigidBody->setSleepingThresholds(0.0, 0.0);
	mRigidBody->setAngularFactor(0.0);
	mRigidBody->setActivationState(DISABLE_DEACTIVATION);
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
}

void Player::Render(const glm::mat4 &projection, const glm::mat4 &view, Shader* shader)
{
}