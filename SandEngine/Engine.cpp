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

	Time::Initialize();

	InitShaders();
	renderer = new SpriteRenderer(ShaderManager::GetShaderByName("default")->ID);
	computeShader = ShaderManager::GetShaderByName("computeTest");
	computeShaderTexture = new Texture(WindowWidth / Engine::Downscaling, WindowHeight / Engine::Downscaling);
	ShaderManager::GetShaderByName("default")->Activate();
	ShaderManager::GetShaderByName("default")->SetInt("img", 0);
	computeShaderTexture->Bind();

	c_data.assign((Engine::WindowWidth / Engine::Downscaling) * (Engine::WindowHeight / Engine::Downscaling), {0});
	m_data.assign((Engine::WindowWidth / Engine::Downscaling) * (Engine::WindowHeight / Engine::Downscaling), {0});
	computeShader->Activate();
	computeShader->CreateBuffers();
	// Send the current scene (readonly) data to the buffer
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, computeShader->currentSceneBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, c_data.size() * sizeof(Particle), c_data.data(), GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, computeShader->modifiedSceneBuffer);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_data.size() * sizeof(Particle), m_data.data(), GL_DYNAMIC_DRAW);

	//testTexture = new Texture("resources/textures/test2.png");
}

int Engine::InitShaders()
{
	log::println("LOADING SHADERS..");

	ShaderManager::LoadAll("resources/shaders/");

	check_gl_error();

	return 1;
}

float lastFrameTime = 0.0f;

void Engine::Step()
{
	if (gl_has_error())
	{
		while (true) {}
	}

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	computeShader->SetInt("windowWidth", Engine::WindowWidth / Engine::Downscaling);
	computeShader->SetInt("windowHeight", Engine::WindowWidth / Engine::Downscaling);

	if (Time::time > lastFrameTime + 0.1f)
	{

		computeShader->Activate();


		// upload c_data to the shader
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, computeShader->currentSceneBuffer);
		glBufferData(GL_SHADER_STORAGE_BUFFER, c_data.size() * sizeof(Particle), c_data.data(), GL_DYNAMIC_DRAW);

		computeShader->Execute(WindowWidth / Engine::Downscaling, WindowHeight / Engine::Downscaling);

		// read m_data and store it in c_data
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, computeShader->modifiedSceneBuffer);
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, c_data.size() * sizeof(Particle), c_data.data());

		lastFrameTime = Time::time;
	}

	renderer->DrawSprite(computeShaderTexture, glm::vec2(0), glm::vec2(Engine::Downscaling));

	

	Time::Update();



	

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
