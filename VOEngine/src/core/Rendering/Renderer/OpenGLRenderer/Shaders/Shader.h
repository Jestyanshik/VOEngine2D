#pragma once
#include "../../Shaders/BaseShader.h"


class Shader : BaseShader{
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();
	const unsigned int getProgram() { return m_Program; };
	void use();
private:
	unsigned int m_Program;
	std::string m_VertexShaderString;
	std::string m_FragmentShaderString;

private:
	unsigned int compileShader(unsigned int type, const std::string& source);
	std::string readFileAsString(std::string_view filename);
};

