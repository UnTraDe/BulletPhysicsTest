#include "Bullet.h"

const Vertex Bullet::CubeVertices[] = {
	//Left
	Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.0f, 0.0f) },

	//Front
	Vertex{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -0.5f) },
	Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -0.5f) },
	Vertex{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -0.5f) },
	Vertex{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -0.5f) },
	Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -0.5f) },
	Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -0.5f) },

	//Bottom
	Vertex{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -0.5f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -0.5f, 0.0f) },
	Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -0.5f, 0.0f) },
	Vertex{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -0.5f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -0.5f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -0.5f, 0.0f) },

	//Back
	Vertex{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f) },
	Vertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f) },
	Vertex{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f) },
	Vertex{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f) },
	Vertex{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f) },
	Vertex{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.5f) },

	//Right
	Vertex{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.0f, 0.0f) },

	//Top
	Vertex{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.5f, 0.0f) },
	Vertex{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.5f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.5f, 0.0f) },
	Vertex{ glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.5f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.5f, 0.0f) },
	Vertex{ glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.5f, 0.0f) }
};

int Bullet::mInstanceCounter = 0;
GLuint Bullet::mVao = 0;
GLuint Bullet::mVbo = 0;
btCollisionShape* Bullet::mShape = nullptr;

Bullet::Bullet()
{
	if (mInstanceCounter == 0)
	{
		glGenBuffers(1, &mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*) 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*) 12);
		glBindVertexArray(0);

		mShape = new btSphereShape(0.1f);
	}
	
	mMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	btScalar mass = 0.2f;
	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, mMotionState, mShape, inertia);
	mRigidBody = new btRigidBody(rigidBodyCI);
	mRigidBody->setCcdMotionThreshold(0.1f);
	mRigidBody->setCcdSweptSphereRadius(0.01f);
	mRigidBody->setActivationState(DISABLE_DEACTIVATION);
	mInstanceCounter++;
}


Bullet::~Bullet()
{
	mInstanceCounter--;

	if (mInstanceCounter == 0) //Is the last object of it's kind
	{
		glDeleteBuffers(1, &mVbo);
		mVbo = 0;

		glDeleteVertexArrays(1, &mVao);
		mVao = 0;

		delete mShape;
		mShape = nullptr;
	}
}

void Bullet::Update(float deltaTime)
{
	age++;
}

void Bullet::Render(const glm::mat4 &projection, const glm::mat4 &view, Shader* shader)
{
	ResourceManager* resources = ResourceManager::GetInstance();

	shader->Bind();
	GLuint vpLocation = shader->GetUniformLocation("VP");
	GLuint modelLocation = shader->GetUniformLocation("Model");
	GLuint invTranLocation = shader->GetUniformLocation("InversedTransform");
	GLuint colorLocation = shader->GetUniformLocation("normalColor");

	btTransform trans;
	mRigidBody->getMotionState()->getWorldTransform(trans);
	btVector3 v = trans.getOrigin();

	glm::mat4 m;
	trans.getOpenGLMatrix((btScalar*) &m);

	glm::mat4 model = m * glm::scale(glm::vec3(0.2f));

	glUniformMatrix4fv(vpLocation, 1, GL_FALSE, &(projection * view)[0][0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(invTranLocation, 1, GL_FALSE, &(glm::translate(-glm::vec3(v.getX(), v.getY(), v.getZ())))[0][0]);
	glUniform3fv(colorLocation, 1, &(glm::vec3(0,0,0))[0]);

	glBindVertexArray(mVao);


	glDrawArrays(GL_TRIANGLES, 0, (sizeof(CubeVertices) / (sizeof(GLfloat) * 6)));

	glBindVertexArray(0);
}