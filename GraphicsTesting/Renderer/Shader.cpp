#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../../thirdparty/glad/include/glad/glad.h"


std::string GetFileContents(const char* fileName)
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
	return {};
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode = GetFileContents(vertexPath);
	std::string fragmentCode = GetFileContents(fragmentPath);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);

	int success;
	char infoLog[512];
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
		return;
	}

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
			infoLog << std::endl;

		return;
	}

	m_rendererID = glCreateProgram();
	glAttachShader(m_rendererID, vertex);
	glAttachShader(m_rendererID, fragment);
	glLinkProgram(m_rendererID);

	glGetProgramiv(m_rendererID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(m_rendererID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
			infoLog << std::endl;
		return;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	std::cout << "Shader created" << std::endl;
}

Shader::~Shader()
{
	glDeleteProgram(m_rendererID);
}

int Shader::GetUniformLocation(const char* name)
{
	if(m_uniformLocationCache.contains(name))
	{
		return m_uniformLocationCache[name];
	}

	int location = glGetUniformLocation(m_rendererID, name);

	if(location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}

	m_uniformLocationCache[name] = location;
	return location;
}

void Shader::SetBool(const char* name, bool value)
{
	glUniform1i(GetUniformLocation(name), (int)value);
}

void Shader::SetInt(const char* name, int value)
{
	glUniform1i(GetUniformLocation(name), value);

}

void Shader::SetFloat(const char* name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec3(const char* name, float x, float y, float z)
{
	glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetVec4(const char* name, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetMatrix4fv(const char* name, float* value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value);
}

void Shader::Use()
{
	glUseProgram(m_rendererID);
}
