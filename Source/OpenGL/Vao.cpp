#include "Vao.h"

Vao::Vao()
{
	glCreateVertexArrays(1, &m_id);
}

Vao::~Vao()
{
	glDeleteVertexArrays(1, &m_id);
}

void Vao::addBuffer(const Vbo& vbo, const VboLayout& layout)
{
	bind();
	vbo.bind();
	const std::vector<VboElement>& elements = layout.getElements();
	uint32_t offset = 0;
	for (size_t i = 0; i < elements.size(); i++)
	{
		const VboElement& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
		offset += element.count * VboElement::getSizeOfType(element.type);
	}
	unbind();
	vbo.unbind();
}

void Vao::bind() const
{
	glBindVertexArray(m_id);
}

void Vao::unbind() const
{
	glBindVertexArray(0);
}
