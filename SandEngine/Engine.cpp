#include "Engine.h"
#include "Texture.h"
#include "SpriteRenderer.h"

Texture* testTexture;
SpriteRenderer* renderer;
Shader* computeShader;
Texture* computeShaderTexture;

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

	glfwSetWindowSizeCallback(window, OnWindowResize);
	

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSwapInterval(0);
	glViewport(0, 0, WindowWidth, WindowHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);

	

	InitShaders();
	renderer = new SpriteRenderer(ShaderManager::GetShaderByName("default")->ID);
	computeShader = ShaderManager::GetShaderByName("computeTest");
	computeShaderTexture = new Texture(WindowWidth / 4, WindowHeight / 4);
	ShaderManager::GetShaderByName("default")->Activate();
	ShaderManager::GetShaderByName("default")->SetInt("img", 0);
	computeShaderTexture->Bind();


	//testTexture = new Texture("resources/textures/test2.png");
}

int Engine::InitShaders()
{
	log::println("LOADING SHADERS..");

	ShaderManager::LoadAll("resources/shaders/");

	check_gl_error();

	return 1;
}

void Engine::Step()
{
	if (gl_has_error())
	{
		while (true) {}
	}

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	
	computeShader->Activate();
	computeShader->Execute(WindowWidth / 4, WindowHeight / 4);

	renderer->DrawSprite(computeShaderTexture, glm::vec2(0), glm::vec2(4));





	//renderer->DrawSprite(testTexture);

	glfwSwapBuffers(window);
	glfwPollEvents();

}

void Engine::OnWindowResize(GLFWwindow* window, int width, int height)
{
	WindowWidth = width;
	WindowHeight = height;
	glViewport(0, 0, WindowWidth, WindowHeight);
}
