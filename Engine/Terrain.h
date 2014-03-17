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
private:
	static const Vertex vertices[];
	GLuint mVao;
	GLuint mVbo;
	GLuint mIbo;
	GLuint mNormalVbo;
	int restartIndex;
	int mapWidth;
	int mapHeight;

	//Properties
	glm::vec3 mColor;

	btRigidBody* mRigidBody;
};

