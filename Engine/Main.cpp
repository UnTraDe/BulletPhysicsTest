#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "World.h"
#include "ResourceManager.h"

int main(int argc, char const *argv[])
{
    if (!glfwInit())
        return -1;

	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Engine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
	
    glfwMakeContextCurrent(window);

	glewExperimental = true;
	glewInit();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glClearColor(0.53, 0.81, 0.98, 1);
	ResourceManager::CreateInstance();

	World* world = new World(glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f));
	world->Initialize();

	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
		world->Update(0, window); //TODO Pass an acutal timestep delta
		world->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	delete world;

    glfwTerminate();

    return 0;
}