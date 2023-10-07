#include "Shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cerrno>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


std::string getFileContents(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	return std::string();
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Shader compilation error: " << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Shader compilation error: " << infoLog << std::endl;
	}

	m_RendererID = glCreateProgram();
	glAttachShader(m_RendererID, vertexShader);
	glAttachShader(m_RendererID, fragmentShader);
	glLinkProgram(m_RendererID);

	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
		std::cerr << "Shader program linking error: " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	Delete();
}

unsigned int Shader::GetUniformLocation(const char* name)
{
	Activate();

	if(uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name);
	uniformLocationCache[name] = location;

	return 0;
}

void Shader::Activate()
{
	glUseProgram(m_RendererID);
}

void Shader::Delete()
{
	glDeleteProgram(m_RendererID);
}
