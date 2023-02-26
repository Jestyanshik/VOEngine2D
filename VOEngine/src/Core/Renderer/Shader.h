#pragma once

class Shader {
public:
	int getID() { return m_ID; };
	Shader(const std::filesystem::path& vertexShaderPath,
		const std::filesystem::path& fragmentShaderPath): m_ID(0){}
protected:
	int m_ID;
};