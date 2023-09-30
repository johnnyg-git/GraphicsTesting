#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	Delete();
}

void VertexArray::LinkAttrib(VertexBuffer& vertexBuffer, unsigned int layout, unsigned int numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	vertexBuffer.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vertexBuffer.Unbind();
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::Delete()
{
	glDeleteVertexArrays(0, &m_RendererID);
}
