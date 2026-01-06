#pragma once
#include <map>
#include "Shader.h"
class ShaderManager
{
public:
	static void Load(std::string name, const char* vert, const char* frag);
	static void LoadAll(std::string root);
	static Shader* GetShaderByName(const char* name);
	static Shader* GetShaderByID(long id);
	static GLuint GetShaderID(const char* name);
	static std::map<int, Shader*> GetShaders();
	static void DeleteAll();
private:
	inline static std::map<int, Shader*> shaders;
};