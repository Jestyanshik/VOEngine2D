#pragma once

class Shader {
public:
	int getID() { return m_ID; };
	Shader(const std::filesystem::path& vertexShaderPath,
		const std::filesystem::path& fragmentShaderPath);
	~Shader();

private:
	uint32_t compileShader(uint32_t type, const std::string& source);
	std::string readFileAsString(std::string_view filename);
private:
	std::string m_VertexShaderString;
	std::string m_FragmentShaderString;
	int m_ID = 0;
};
