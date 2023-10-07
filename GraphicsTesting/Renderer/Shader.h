#pragma once
#include <unordered_map>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	int GetUniformLocation(const char* name);

	void SetBool(const char* name, bool value);
	void SetInt(const char* name, int value);
	void SetFloat(const char* name, float value);

	void Use() const;

private:
	unsigned int m_rendererID;
	std::unordered_map<const char*, int> m_uniformLocationCache;
};
