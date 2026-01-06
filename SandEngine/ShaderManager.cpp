#include "ShaderManager.h"
#include <filesystem>
#include <regex>
namespace fs = std::filesystem;

void ShaderManager::Load(std::string name, const char* vert, const char* frag)
{
	Shader* shader = new Shader(vert, frag);
	shader->name = name;
	shaders.insert(std::make_pair(shader->ID, shader));
}

void ShaderManager::Load(std::string name, const char* comp)
{
	Shader* shader = new Shader(comp);
	shader->name = name;
	shaders.insert(std::make_pair(shader->ID, shader));
}

void ShaderManager::LoadAll(std::string root)
{
	for (const auto& entry : fs::directory_iterator(root))
		if (entry.is_regular_file())
		{
			if (entry.path().extension() == ".vert")
			{
				std::string filename = entry.path().filename().string();
				filename = filename.substr(0, filename.find_last_of("."));

				std::string vertPath = entry.path().string();
				std::string fragPath = entry.path().string();

				Load(filename, vertPath.c_str(), std::regex_replace(fragPath, std::regex(".vert"), ".frag").c_str());
			}
			if (entry.path().extension() == ".comp")
			{
				std::string filename = entry.path().filename().string();
				filename = filename.substr(0, filename.find_last_of("."));

				std::string compPath = entry.path().string();
				std::string fragPath = entry.path().string();

				Load(filename, compPath.c_str());
			}
		}
}

Shader* ShaderManager::GetShaderByName(const char* name)
{
	for (auto const& sha : shaders)
	{
		if (sha.second->name == name)
		{
			return sha.second;
		}
	}
	std::cout << "Failed to locate shader " << name << std::endl;
	return nullptr;
}

Shader* ShaderManager::GetShaderByID(long id)
{
	if (shaders.count(id))
	{
		return shaders[id];
	}
	std::cout << "Failed to locate shader from ID " << id << std::endl;
	return nullptr;
}

GLuint ShaderManager::GetShaderID(const char* name)
{
	for (auto const& [key, obj] : shaders)
	{
		if (obj->name == std::string(name))
		{
			return obj->ID;
		}
	}
	std::cout << "Failed to locate shader " << name << std::endl;
	return -1;
}

std::map<int, Shader*> ShaderManager::GetShaders()
{
	return shaders;
}

void ShaderManager::DeleteAll()
{
	for (auto const& [key, obj] : shaders)
	{
		obj->Delete();
	}
}