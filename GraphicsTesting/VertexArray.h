#pragma once

#include "VertexBuffer.h"

class VertexArray {
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void LinkVertexBuffer(VertexBuffer& vertexBuffer, unsigned int layout);
	void Bind();
	void Unbind();
	void Delete();
};