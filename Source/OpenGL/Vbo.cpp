#include "Vbo.h"

Vbo::Vbo(const void* data, uint32_t size)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

Vbo::~Vbo()
{
	glDeleteBuffers(1, &m_id);
}

void Vbo::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void Vbo::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
