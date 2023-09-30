#pragma once
#include <sstream>

std::string getFileContents(const char* fileName);

class Shader {
private:
	unsigned int m_RendererID;

public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void Activate();
	void Delete();

	inline unsigned int GetRendererID() const { return m_RendererID; }
};