#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "World.h"

int main(int argc, char const *argv[])
{
    if (!glfwInit())
        return -1;

	GLFWwindow* window = glfwCreateWindow(800, 600, "Engine", NULL, NULL);
	
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
	
    glfwMakeContextCurrent(window);

	glewExperimental = true;
	glewInit();

	World* world = new World(glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 1000.0f));
	world->Initialize();

    while (!glfwWindowShouldClose(window))
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