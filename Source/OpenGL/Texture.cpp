#include "Texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& imageFilepath)
{
	uint8_t* data = stbi_load(imageFilepath.c_str(), &m_width, &m_height, &m_channels, 0);

	uint32_t textureFormat = GL_RGBA;
	uint32_t internalFormat = GL_RGBA32F;
	if (m_channels == 3) {
		textureFormat = GL_RGB;
		internalFormat = GL_RGB32F;
	}

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, textureFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::bindToSlot(uint32_t slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	bind();
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
