#pragma once
#include <sstream>
#include <unordered_map>

#include "glm/fwd.hpp"

std::string getFileContents(const char* fileName);

class Shader {
private:
	unsigned int m_RendererID;
	std::unordered_map<const char*, int> uniformLocationCache;

public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	unsigned int GetUniformLocation(const char* name);



	void Activate();
	void Delete();

	inline unsigned int GetRendererID() const { return m_RendererID; }
};