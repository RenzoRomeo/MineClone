#include "Shader.h"

#include "../Application/Logging.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::ifstream vertexFile;
	std::stringstream vertexSourceStream;

	vertexFile.open(vertexPath);
	vertexSourceStream << vertexFile.rdbuf();
	vertexFile.close();

	std::string vertexSourceString = vertexSourceStream.str();
	const char* vertexSource = vertexSourceString.c_str();
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, 0);
	glCompileShader(vertexShader);

	int32_t success;
	char infoLog[1024];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
		LOG(LogType::ERROR, "Vertex shader compilation failed");
		LOG(LogType::ERROR, infoLog);
	}

	std::ifstream fragmentFile;
	std::stringstream fragmentSourceStream;

	fragmentFile.open(fragmentPath);
	fragmentSourceStream << fragmentFile.rdbuf();
	fragmentFile.close();

	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentSourceString = fragmentSourceStream.str();
	const char* fragmentSource = fragmentSourceString.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSource, 0);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
		LOG(LogType::ERROR, "Fragment shader compilation failed");
		LOG(LogType::ERROR, infoLog);
	}

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_id, 1024, NULL, infoLog);
		LOG(LogType::ERROR, "Shader program linking failed");
		LOG(LogType::ERROR, infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::use()
{
	glUseProgram(m_id);
}

void Shader::setUniformMat4(const std::string& name, const glm::mat4& mat4)
{
	use();
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat4[0][0]);
}

void Shader::setUniform1i(const std::string& name, int value)
{
	use();
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1f(const std::string& name, float value)
{
	use();
	glUniform1f(getUniformLocation(name), value);
}

int32_t Shader::getUniformLocation(const std::string& name)
{
	return glGetUniformLocation(m_id, name.c_str());
}
