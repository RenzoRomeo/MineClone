#include "Ebo.h"

Ebo::Ebo()
	: m_count(0)
{

}

Ebo::Ebo(const uint32_t* data, uint32_t count)
	: m_count(count)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

Ebo::~Ebo()
{
	glDeleteBuffers(1, &m_id);
}

void Ebo::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void Ebo::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
