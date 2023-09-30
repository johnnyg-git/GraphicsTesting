#include "VertexArray.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	Delete();
}

void VertexArray::LinkVertexBuffer(VertexBuffer& vertexBuffer, unsigned int layout)
{
	vertexBuffer.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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
