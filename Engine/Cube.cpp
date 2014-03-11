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

int Cube::mInstanceCounter = 0;
GLuint Cube::mVao = 0;
GLuint Cube::mVbo = 0;
btCollisionShape* Cube::mShape = nullptr;

Cube::Cube(glm::vec3 color)
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)12);
		glBindVertexArray(0);

		mShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
	}

	//Properties
	mColor = color;

	//Physics
	mMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));

	btScalar mass = 1;
	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, mMotionState, mShape, inertia);
	mRigidBody = new btRigidBody(rigidBodyCI);
	
	mInstanceCounter += 1;
}

Cube::~Cube()
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
	GLuint invTranLocation = shader->GetUniformLocation("InversedTransform");
	GLuint colorLocation = shader->GetUniformLocation("normalColor");
	
	btTransform trans;
	mRigidBody->getMotionState()->getWorldTransform(trans);
	btVector3 v = trans.getOrigin();
	
	glm::mat4 m;
	trans.getOpenGLMatrix((btScalar*)&m);

	glm::mat4 model = m * glm::mat4(1.0f);

	glUniformMatrix4fv(vpLocation, 1, GL_FALSE, &(projection * view)[0][0]);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(invTranLocation, 1, GL_FALSE, &(glm::translate(-glm::vec3(v.getX(), v.getY(), v.getZ())))[0][0]);
	glUniform3fv(colorLocation, 1, &mColor[0]);

	glBindVertexArray(mVao);

	glDrawArrays(GL_TRIANGLES, 0, (sizeof(CubeVertices) / (sizeof(GLfloat) * 6)));
}