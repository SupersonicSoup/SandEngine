#pragma once
#include "Texture.h"
#include "Shader.h"
#include "ShaderManager.h"

class SpriteRenderer
{
public:
	SpriteRenderer(GLuint shader);
	// Deconstructor
	~SpriteRenderer();

	void DrawSprite(Texture* texture, glm::vec2 position = glm::vec2(0),
		glm::vec2 size = glm::vec2(1.0f, 1.0f), float rotate = 0.0f,
		glm::vec4 color = glm::vec4(1.0f), int zIndex = 0, bool mipmapped = false, bool repeat = true);
private:
	GLuint shader;
	GLuint VAO;
	void init();
};