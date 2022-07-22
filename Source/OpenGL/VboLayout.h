#pragma once

struct VboElement
{
	uint32_t type;
	uint32_t count;
	uint32_t normalized;

	static uint32_t getSizeOfType(uint32_t type)
	{
		switch (type)
		{
		case GL_UNSIGNED_BYTE: return 1;
		case GL_UNSIGNED_INT: return 4;
		case GL_FLOAT: return 4;
		}
		return 0;
	}
};

class VboLayout
{
public:
	VboLayout()
		: m_stride(0) {}

	template<typename t>
	void push(uint32_t count)
	{

	}

	template<>
	void push<float>(uint32_t count)
	{
		m_elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_stride += count * VboElement::getSizeOfType(GL_FLOAT);
	}

	template<>
	void push<uint32_t>(uint32_t count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += count * VboElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void push<uint8_t>(uint32_t count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += count * VboElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VboElement>& getElements() const { return m_elements; }

	inline uint32_t getStride() const { return m_stride; }

private:
	std::vector<VboElement> m_elements;
	uint32_t m_stride;
};