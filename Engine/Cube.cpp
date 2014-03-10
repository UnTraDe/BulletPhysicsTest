#include "Cube.h"

/*const glm::vec3 Cube::CubeVertices[] = {
	//Left
	glm::vec3(- 1.0f, -1.0f, -1.0f),
	glm::vec3(- 1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),

	//Front
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),

	//Bottom
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),

	//Back
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),

	//Right
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, -1.0f, 1.0f),

	//Top
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(-1.0f, 1.0f, -1.0f),
	glm::vec3(-1.0f, 1.0f, 1.0f)
};*/

const Vertex Cube::CubeVertices[] = {
	//Left
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f) },

	//Front
	Vertex{ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
	Vertex{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
	Vertex{ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
	Vertex{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f) },

	//Bottom
	Vertex{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f) },

	//Back
	Vertex{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
	Vertex{ glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
	Vertex{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
	Vertex{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
	Vertex{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
	Vertex{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) },

	//Right
	Vertex{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) },

	//Top
	Vertex{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }
};

int Cube::mInstanceCounter = 0;
GLuint Cube::mVao = 0;
GLuint Cube::mVbo = 0;


Cube::Cube(int size, btDiscreteDynamicsWorld* dynamicsWorld) : Object()
{
	if (mVbo == 0)
	{
		glGenBuffers(1, &mVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if (mVao == 0)
	{
		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);
		glBindBuffer(GL_ARRAY_BUFFER, mVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
		glBindVertexArray(0);
	}

	mModel = glm::mat4(1.0f);

	mInstanceCounter += 1;

	//Physics
	btCollisionShape* fallShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	btDefaultMotionState* fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));

	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
}

Cube::~Cube()
{
	mInstanceCounter--;

	if (mInstanceCounter == 0)
	{
		glDeleteBuffers(1, &mVbo);
		glDeleteVertexArrays(1, &mVao);
	}
}

void Cube::Update(float deltaTime)
{
	
}

void Cube::Render(const glm::mat4 &projection, const glm::mat4 &view)
{
	ResourceManager* resources = ResourceManager::GetInstance();

	Shader *shader = resources->GetShader("default");

	shader->Bind();

	GLuint vpLocation = shader->GetUniformLocation("VP");
	GLuint modelLocation = shader->GetUniformLocation("Model");
	
	btTransform trans;
	fallRigidBody->getMotionState()->getWorldTransform(trans);
	btVector3 v = trans.getOrigin();
	
	glm::quat q(trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ(), trans.getRotation().getW());
	glm::vec3 pos(v.getX(), v.getY(), v.getZ());
	
	std::cout << trans.getRotation().getAngle() << std::endl;

	glm::mat4 model = glm::translate(pos) * glm::toMat4(q) * mModel;

	glUniformMatrix4fv(vpLocation, 1, GL_FALSE, &(projection * view)[0][0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(mVao);

	glDrawArrays(GL_TRIANGLES, 0, (sizeof(CubeVertices) / (sizeof(GLfloat) * 6)));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}