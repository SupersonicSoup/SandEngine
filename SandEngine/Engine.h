#pragma once
#include "log.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GLError.h"

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
	static void Step();
	static bool ShouldClose()
	{
		return glfwWindowShouldClose(window);
	}
	static void Shutdown();
	static GLFWwindow* GetWindow()
	{
		return window;
	}

private:
	inline static int WindowWidth = 320;
	inline static int WindowHeight = 240;
	inline static GLFWwindow* window;
};