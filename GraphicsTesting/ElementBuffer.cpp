#include "ElementBuffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

ElementBuffer::ElementBuffer(const unsigned int* data, unsigned int size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void ElementBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void ElementBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
