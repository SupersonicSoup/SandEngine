#include "Texture.h"
#include "GLError.h"

Texture::Texture() {
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
};

Texture::Texture(int w, int h)
{
	width = w;
	height = h;
	channels = 4;
	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindImageTexture(0, ID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

Texture::Texture(const char* filename)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture: " << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
	}
	stbi_image_free(data);
}

// Returns loaded data before destroying
Texture::Texture(unsigned char*& data, const char* filename)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(filename, &width, &height, &channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture: " << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
	}
	// Data is NOT freed with this constructor, make sure to free it when it is used.
	//stbi_image_free(data);
}

void Texture::SetData(unsigned char* data)
{
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::SetTiling(bool _tile)
{
	tile = _tile;
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::BindImage()
{
	glActiveTexture(GL_TEXTURE0);
	glBindImageTexture(0, ID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}