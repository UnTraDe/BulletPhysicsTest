#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <bullet/btBulletDynamicsCommon.h>

#include "ResourceManager.h"
#include "FPSCamera.h"
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
	std::vector<Object*> mObjects;

	btDiscreteDynamicsWorld* dynamicsWorld;
};