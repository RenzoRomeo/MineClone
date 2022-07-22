#pragma once

#include "../core.h"

class Vbo
{
public:
	Vbo(const void* data, uint32_t size);
	~Vbo();
	
	void bind() const;

	void unbind() const;

private:
	uint32_t m_id;
};