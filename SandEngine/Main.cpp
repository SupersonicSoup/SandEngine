#include "log.h"
#include "Engine.h"

int main(void)
{
	Engine::Initialize("Falling Sand");
	log::println("Hello world!");

	while (!Engine::ShouldClose())
	{
		if (glfwGetKey(Engine::GetWindow(), GLFW_KEY_R))
		{
			glfwSetWindowShouldClose(Engine::GetWindow(), true);
		}

		Engine::Step();
	}
	return 0;
}