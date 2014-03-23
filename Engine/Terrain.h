#pragma once
#include <glm/ext.hpp>
#include <GL/glew.h>
#include "ResourceManager.h"
#include "CommonData.h"
#include <glm/glm.hpp>
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include "SimplexNoise.h"
#include "bullet\BulletCollision\CollisionShapes\btConvexShape.h"

class Terrain
{
public:
	Terrain(int size);
	~Terrain();
	void Render(const glm::mat4 &projection, const glm::mat4 &view);
	btRigidBody* GetRigidBody() { return mRigidBody; };
	int GetMapWidth() { return mapWidth; };
	int GetMapHeight() { return mapHeight; };
private:
	static const Vertex vertices[];
	GLuint mTextureId;
	GLuint mVao;
	GLuint mVbo;
	GLuint mIndexVbo;
	GLuint mNormalVbo;
	GLuint mTextureCoordinatesVbo;
	int restartIndex;
	int mapWidth;
	int mapHeight;

	//Properties
	glm::vec3 mColor;

	btRigidBody* mRigidBody;
};

