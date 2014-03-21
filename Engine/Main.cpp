#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "World.h"
#include "ResourceManager.h"

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	std::cout << std::endl;
	system("pause");
}

int main(int argc, char const *argv[])
{
    if (!glfwInit())
        return -1;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwSetErrorCallback(error_callback);
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

	World* world = new World(glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 10000.0f));
	world->Initialize();
	int frames = 0;
	double lastFrame = glfwGetTime();

	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
		frames++;
		if (glfwGetTime() - lastFrame >= 1.0)
		{
			std::string s = "Engine - ";
			s.append(std::to_string(frames));
			s.append(" - Objects: ");
			s.append(std::to_string(world->GetObjects()));
			glfwSetWindowTitle(window, s.c_str());
			lastFrame = glfwGetTime();
			frames = 0;
		}
		world->Update(0, window); //TODO Pass an acutal timestep delta
		world->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	delete world;

    glfwTerminate();

    return 0;
}