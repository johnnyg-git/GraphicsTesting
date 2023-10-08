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
	void SetVec3(const char* name, float x, float y, float z);
	void SetVec4(const char* name, float x, float y, float z, float w);
	void SetMatrix4fv(const char* name, float* value);

	void Use();

private:
	unsigned int m_rendererID;
	std::unordered_map<const char*, int> m_uniformLocationCache;
};
