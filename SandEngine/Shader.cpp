#include "Shader.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader() {};

Shader::Shader(const char* vert, const char* frag)
{
	std::string _vert = get_file_contents(vert);
	std::string _frag = get_file_contents(frag);

	const char* vertSrc = _vert.c_str();
	const char* fragSrc = _frag.c_str();

	GLint shaderSuccess;

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertSrc, NULL);
	glCompileShader(vertShader);
	checkErrors(vertShader, "VERTEX", shaderSuccess);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragSrc, NULL);
	glCompileShader(fragShader);
	checkErrors(fragShader, "FRAGMENT", shaderSuccess);

	ID = glCreateProgram();
	glAttachShader(ID, vertShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);
	checkErrors(ID, "PROGRAM", shaderSuccess);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	if (shaderSuccess)
	{
		std::cout << " [Shader Manager] Loaded " << vert << std::endl;
	}
	else
	{
		std::cout << "SHADER COMPILATION FAILED" << std::endl;
	}
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::SetMatrix(const char* uniform, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, uniform), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetFloat(const char* uniform, float f)
{
	glUniform1f(glGetUniformLocation(ID, uniform), f);
}

void Shader::SetVec2(const char* uniform, glm::vec2 vec)
{
	glUniform2f(glGetUniformLocation(ID, uniform), vec.x, vec.y);
}

void Shader::SetVec3(const char* uniform, glm::vec3 vec)
{
	glUniform3f(glGetUniformLocation(ID, uniform), vec.x, vec.y, vec.z);
}

void Shader::SetVec4(const char* uniform, glm::vec4 vec)
{
	glUniform4f(glGetUniformLocation(ID, uniform), vec.x, vec.y, vec.z, vec.w);
}

// Checks if the different Shaders have compiled properly
void Shader::checkErrors(unsigned int shader, const char* type, GLint& success)
{
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}