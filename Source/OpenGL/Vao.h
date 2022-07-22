#pragma once

#include "../core.h"

#include "Vbo.h"
#include "VboLayout.h"

class Vao
{
public:
	Vao();
	~Vao();

	void addBuffer(const Vbo& vbo, const VboLayout& layout);

	void bind() const;

	void unbind() const;

private:
	uint32_t m_id;
};