#pragma once
#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.h"

class Texture
{
public:
	GLuint ID;
	std::string name;
	int width;
	int height;
	int channels;
	bool tile = false;
	void Bind();
	void Unbind();

	Texture();
	Texture(const char* filename);
	Texture(unsigned char*& data, const char* filename);
	Texture(unsigned char*& data);
	void SetData(unsigned char* data);
	void SetTiling(bool _tile);
private:

};