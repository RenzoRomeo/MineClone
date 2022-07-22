#pragma once

#include "../core.h"

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use();

	void setUniformMat4(const std::string& name, const glm::mat4& mat4);

	void setUniform1i(const std::string& name, int value);

	void setUniform1f(const std::string& name, float value);

private:
	int32_t getUniformLocation(const std::string& name);

private:
	uint32_t m_id;
};