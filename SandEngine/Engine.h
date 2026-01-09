#pragma once
#include "log.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GLError.h"
#include "ShaderManager.h"
#include "particle.h"
#include "Time.h"

class Engine
{
private:
	Engine();
	~Engine();
public:
	static Engine& getInstance()
	{
		static Engine instance;
		return instance;
	}

	static int Initialize(std::string title);
	static int InitShaders();
	static void Step();
	static void OnWindowResize(GLFWwindow* window, int width, int height);
	static bool ShouldClose()
	{
		return glfwWindowShouldClose(window);
	}
	static void Shutdown();
	static GLFWwindow* GetWindow()
	{
		return window;
	}

	inline static int WindowWidth = 800;
	inline static int WindowHeight = 600;
	inline static int Downscaling = 4;
	inline static std::vector<Particle> c_data;
	inline static std::vector<Particle> m_data;
	inline static std::vector<uint32_t> claimsData;

private:
	inline static GLFWwindow* window;
};