#include "ObjectModel.h"


ObjectModel::ObjectModel(const glm::vec3 startPos, Model* model, btCollisionShape* shape)
{
	this->model = model;

	mShape = shape;
	//Physics
	mMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(startPos.x, startPos.y, startPos.z)));
	btScalar mass = 5;
	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, mMotionState, mShape, inertia);
	mRigidBody = new btRigidBody(rigidBodyCI);
	mRigidBody->setFriction(5.0);
}


ObjectModel::~ObjectModel()
{
}

void ObjectModel::Update(float deltaTime)
{

}

void ObjectModel::Render(const glm::mat4 &projection, const glm::mat4 &view, Shader* shader)
{
	btTransform trans;
	mRigidBody->getMotionState()->getWorldTransform(trans);

	glm::mat4 m;
	trans.getOpenGLMatrix((btScalar*) &m);

	model->RenderModel(shader, projection, view, this->GetPosition(), m);
}
