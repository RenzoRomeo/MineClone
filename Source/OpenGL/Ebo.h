#pragma once

#include "../core.h"

class Ebo
{
public:
	Ebo(const uint32_t* data, uint32_t count);
	~Ebo();

	void bind() const;

	void unbind() const;

	inline uint32_t getCount() const { return m_count; }

private:
	uint32_t m_id;
	uint32_t m_count;
};