#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "ShaderManager.h"
#include "TextureManager.h"
#include "FPSCamera.h"
#include "Cube.h"
#include "Crate.h"

class World
{
public:
	World(glm::mat4 projection);
	void Initialize();

	void Update(float deltaTime, GLFWwindow* window);
	void Render();
	

private:
	FPSCamera* mCamera;
	glm::mat4 mProjection;
	std::vector<Object*> mObjects;

	ShaderManager mShaderManager;
	TextureManager mTextureManager;

	void ProcessInput(float deltaTime, GLFWwindow* window);
};