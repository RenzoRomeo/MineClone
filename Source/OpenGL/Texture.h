#pragma once

#include "../core.h"

class Texture
{
public:
	Texture(const std::string& imageFilepath);
	~Texture();

	void bind() const;
	
	void bindToSlot(uint32_t slot) const;
	
	void unbind() const;

private:
	uint32_t m_id;
	int32_t m_width, m_height;
	int32_t m_channels;
};