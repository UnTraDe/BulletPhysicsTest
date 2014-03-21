#pragma once

#include <algorithm> // remove and remove_if
#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/CollisionDispatch/btGhostObject.h>

#include "ResourceManager.h"
#include "FPSCamera.h"
#include "Player.h"
#include "Cube.h"
#include "Crate.h"
#include "Bullet.h"
#include "Terrain.h"
#include "Gui.h"
#include "Model.h"

class World
{
public:
	World(glm::mat4 projection);
	~World();

	void Initialize();

	void Update(float deltaTime, GLFWwindow* window);
	void Render();
	int GetObjects() { return objects; };

private:
	void ProcessInput(float deltaTime, GLFWwindow* window);
	void Explode(glm::vec3 pos, float power, float radius);

	Gui* mGui;
	FPSCamera* mCamera;
	glm::mat4 mProjection;
	Player *player;
	std::vector<Object*> mObjects;
	double lastShot;
	int objects;
	Terrain* terrain;
	Model* testModel;

	//Physics
	btBroadphaseInterface* mBroadphase;
	btDefaultCollisionConfiguration* mCollisionConfiguration;
	btCollisionDispatcher* mDispatcher;
	btSequentialImpulseConstraintSolver* mSolver;
	btDiscreteDynamicsWorld* mDynamicsWorld;
};