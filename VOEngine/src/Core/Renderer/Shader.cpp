#include "vopch.h"
#include "Shader.h"

Shader::Shader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath) {
	m_FragmentShaderString = readFileAsString(std::filesystem::current_path().string() + '\\' + fragmentShaderPath.string());
	m_VertexShaderString = readFileAsString(std::filesystem::current_path().string() + '\\' + vertexShaderPath.string());

	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, m_VertexShaderString);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, m_FragmentShaderString);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);
	glValidateProgram(m_ID);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(m_ID);
}

uint32_t Shader::compileShader(uint32_t type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		std::string message(length, ' ');
		glGetShaderInfoLog(id, length, &length, message.data());
		VO_CORE_ERROR(message);
		glDeleteShader(id);
		return 0;
	}
	return id;
}

std::string Shader::readFileAsString(std::string_view filename) {
	constexpr auto read_size = std::size_t(4096);
	auto stream = std::ifstream(filename.data());
	stream.exceptions(std::ios_base::badbit);

	auto out = std::string();
	auto buf = std::string(read_size, '\0');
	while (stream.read(&buf[0], read_size)) {
		out.append(buf, 0, stream.gcount());
	}
	out.append(buf, 0, stream.gcount());
	return out;
}
