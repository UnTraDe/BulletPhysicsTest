#include "Terrain.h"

const Vertex Terrain::vertices [] = {
	Vertex{ glm::vec3(1.0f, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, 0, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 0, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(1.0f, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(-1.0f, 0, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f) },
	Vertex{ glm::vec3(-1, 0, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }
};

Terrain::Terrain(const int size)
{
	InitSimplex((int)time(NULL));

	mapWidth = size;
	mapHeight = size;

	int maxHeight = 30;

	int add = rand() % 1000;
	std::vector<glm::vec3> vertices;
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++){
			float noiseR = 0.5f + ((float) noise(add + i / 10.0f, add + j / 10.0f) + 1) / 4.0f;
			vertices.push_back(glm::vec3(i, noiseR * maxHeight, j));
		}
	}

	std::vector<int> indexes;

	restartIndex = mapWidth * mapHeight;

	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				indexes.push_back(((i + (1 - k)) * mapHeight) + j);
			}
		}

		indexes.push_back(restartIndex);
	}

	std::vector<int> realIndicies;
	for (int i = 0; i < mapWidth - 1; i++)
	{
		for (int j = 0; j < mapHeight - 1; j++)
		{
			realIndicies.push_back(j + i * mapHeight);
			realIndicies.push_back((j + 1) + (i + 1) * mapHeight);
			realIndicies.push_back((j + 1) + i * mapHeight);

			realIndicies.push_back(j + i * mapHeight);
			realIndicies.push_back(j + (i + 1) * mapHeight);
			realIndicies.push_back((j + 1) + (i + 1) * mapHeight);
		}
	}

	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3) *mapWidth*mapHeight), &vertices[0][0], GL_STATIC_DRAW);

	glGenBuffers(1, &mIbo);
	glBindBuffer(GL_ARRAY_BUFFER, mIbo);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(int) *realIndicies.size()), &realIndicies[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
	glBindVertexArray(0);

	int* indicesAr = new int[realIndicies.size()];
	for (unsigned int k = 0; k < realIndicies.size(); k++){
		indicesAr[k] = realIndicies[k];
	}

	btScalar* points = new btScalar[vertices.size() * 3];
	unsigned int ptIter = 0;
	for (unsigned int i = 0; i < vertices.size(); i++) {
		
		points[ptIter++] = (btScalar) vertices[i].x;
		points[ptIter++] = (btScalar) vertices[i].y;
		points[ptIter++] = (btScalar) vertices[i].z;
	}
	btTriangleIndexVertexArray* iva = new btTriangleIndexVertexArray(realIndicies.size() / 3, indicesAr, sizeof(int) * 3, vertices.size(), points, sizeof(btScalar) * 3);
	
	//btConvexHullShape* shape = new btConvexHullShape(points, vertices.size(), sizeof(glm::vec3));

	btBvhTriangleMeshShape* tshape = new btBvhTriangleMeshShape(iva, true);

	//btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	//btHeightfieldTerrainShape* shape = new btHeightfieldTerrainShape(mapWidth, mapHeight, heights, 20, 1, true, false);
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, tshape, btVector3(0, 0, 0));
	mRigidBody = new btRigidBody(groundRigidBodyCI);
	mRigidBody->setFriction(0.0);
	//mRigidBody->getWorldTransform().setOrigin(btVector3(0, -1, 0));
}


Terrain::~Terrain()
{
}

void Terrain::Render(const glm::mat4 &projection, const glm::mat4 &view)
{
	ResourceManager* resources = ResourceManager::GetInstance();
	Shader *shader = resources->GetShader("simple");

	shader->Bind();

	GLuint mvpLocation = shader->GetUniformLocation("MVP");

	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(projection * view)[0][0]);

	glBindVertexArray(mVao);

	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(restartIndex);

	int iNumIndices = (mapWidth - 1)*mapHeight * 2 + mapWidth - 1;
	iNumIndices = (mapWidth - 1)*(mapHeight - 1) * 3;
	//iNumIndices = 1000;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, iNumIndices, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}