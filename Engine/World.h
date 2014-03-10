#pragma once

#include <cstdlib>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <bullet/btBulletDynamicsCommon.h>

#include "ResourceManager.h"
#include "FPSCamera.h"
#include "Player.h"
#include "Cube.h"
#include "Crate.h"

class World
{
public:
	World(glm::mat4 projection);
	~World();

	void Initialize();

	void Update(float deltaTime, GLFWwindow* window);
	void Render();
	

private:
	void ProcessInput(float deltaTime, GLFWwindow* window);

	FPSCamera* mCamera;
	glm::mat4 mProjection;
	Player *player;
	std::vector<Object*> mObjects;

	//Physics
	btBroadphaseInterface* mBroadphase;
	btDefaultCollisionConfiguration* mCollisionConfiguration;
	btCollisionDispatcher* mDispatcher;
	btSequentialImpulseConstraintSolver* mSolver;
	btDiscreteDynamicsWorld* mDynamicsWorld;
};