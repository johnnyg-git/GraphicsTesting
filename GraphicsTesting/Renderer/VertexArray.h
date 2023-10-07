#pragma once

#include "VertexBuffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexArray {
private:
	unsigned int m_rendererID;
public:
	VertexArray();
	~VertexArray();

	void LinkAttrib(VertexBuffer& vertexBuffer, unsigned int layout, unsigned int numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
};