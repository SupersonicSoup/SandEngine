#include "Engine.h"

int Engine::Initialize(std::string title)
{
	log::println("Initializing Engine...");

	if (!glfwInit())
	{
		log::println("Engine initilization failed!");
		return -1;
	}

	log::println("Creating window..");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WindowWidth, WindowHeight, "Falling Sand", NULL, NULL);

	if (!window)
	{
		log::println("[ERROR] Could not create window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSwapInterval(0);
	glViewport(0, 0, WindowWidth, WindowHeight);
}

void Engine::Step()
{
	if (gl_has_error())
	{
		while (true) {}
	}

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
	glfwPollEvents();

}
