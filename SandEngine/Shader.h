#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#define VERTEX 0
#define COMPUTE 1

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	GLuint currentSceneBuffer;
	GLuint modifiedSceneBuffer;
	std::string name;
	Shader();
	Shader(const char* vert, const char* frag);
	Shader(const char* compute);
	void CreateBuffers();
	void BindBuffers();
	void SetMatrix(const char* uniform, glm::mat4 matrix);
	void SetFloat(const char* uniform, float v);
	void SetInt(const char* uniform, int i);
	void SetVec2(const char* uniform, glm::vec2 vec);
	void SetVec3(const char* uniform, glm::vec3 vec);
	void SetVec4(const char* uniform, glm::vec4 vec);
	void Activate();
	void Execute(int width, int height);
	void Delete();
private:
	void checkErrors(unsigned int shader, const char* type, GLint& success);
};