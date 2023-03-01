#pragma once
#include "../Shader.h"


class OpenGLShader : public Shader{
public:
	OpenGLShader(const std::filesystem::path& vertexShaderPath,
		const std::filesystem::path& fragmentShaderPath);
	~OpenGLShader();
private:
	std::string m_VertexShaderString;
	std::string m_FragmentShaderString;

private:
	unsigned int compileShader(unsigned int type, const std::string& source);
	std::string readFileAsString(std::string_view filename);
};

