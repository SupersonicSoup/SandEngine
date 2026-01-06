#include "SpriteRenderer.h"
#include "GLError.h"
#include "Engine.h"

SpriteRenderer::SpriteRenderer(GLuint shader)
{
    SpriteRenderer::shader = shader;
    init();
}

void SpriteRenderer::init()
{
    GLuint VBO;
    GLuint EBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    int indices[] = {
        0, 2, 1,
        0, 1, 3
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set up vertex attributes
    // We only need one for the vec4 in the shader
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(Texture* texture, glm::vec2 position,
    glm::vec2 size, float rotation, glm::vec4 color, int zIndex, bool mipmapped, bool repeat)
{
    if (!texture) return;
    ShaderManager::GetShaderByID(shader)->Activate();
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 proj = glm::ortho(0.0f, (float)Engine::WindowWidth, 0.0f, (float)Engine::WindowHeight, -1.0f, 1.0f);
    model = glm::scale(model, glm::vec3(texture->width, texture->height, 1.0f));
    model = glm::translate(model, glm::vec3(position, zIndex));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    ShaderManager::GetShaderByID(shader)->SetMatrix("model", model);
    ShaderManager::GetShaderByID(shader)->SetMatrix("projection", proj);

    glActiveTexture(GL_TEXTURE0);

    // Remember: Bind texture BEFORE changing glTexParameter values
    texture->Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}