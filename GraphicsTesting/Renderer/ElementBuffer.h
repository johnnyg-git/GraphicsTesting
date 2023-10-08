#pragma once

class ElementBuffer {
private:
	unsigned int m_rendererID;
	unsigned int m_count;
public:
	ElementBuffer(const unsigned int* data, unsigned int count);
	~ElementBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_count; }
};