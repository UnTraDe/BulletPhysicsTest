#include "Terrain.h"

const Vertex Terrain::vertices [] = {
	Vertex{ glm::vec3(1.0f, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, 0, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 0, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 0, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(-1, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }
};

Terrain::Terrain()
{
	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*) 12);
	glBindVertexArray(0);

	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	mRigidBody = new btRigidBody(groundRigidBodyCI);
	mRigidBody->setFriction(5.0);
	mRigidBody->getWorldTransform().setOrigin(btVector3(0,-1,0));
	mColor = glm::vec3(0.4f, 0.9f, 0.6f);
}


Terrain::~Terrain()
{
}

void Terrain::Render(const glm::mat4 &projection, const glm::mat4 &view)
{
	ResourceManager* resources = ResourceManager::GetInstance();
	Shader *shader = resources->GetShader("default");

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

	glm::mat4 model = m * glm::scale(glm::vec3(100.0f));

	glUniformMatrix4fv(vpLocation, 1, GL_FALSE, &(projection * view)[0][0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(invTranLocation, 1, GL_FALSE, &(glm::translate(-glm::vec3(v.getX(), v.getY(), v.getZ())))[0][0]);
	glUniform3fv(colorLocation, 1, &mColor[0]);

	glBindVertexArray(mVao);

	glDrawArrays(GL_TRIANGLES, 0, (sizeof(vertices) / (sizeof(GLfloat) * 6)));
}