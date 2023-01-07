#include "vopch.h"
#include "Shader.h"
#include "glad/glad.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	m_VertexShaderString = readFileAsString(vertexShaderPath);
    m_FragmentShaderString = readFileAsString(fragmentShaderPath);

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, m_VertexShaderString);
    assert (vertexShader != 0);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, m_FragmentShaderString);
    assert(fragmentShader != 0);


    m_Program = glCreateProgram();
    glAttachShader(m_Program, vertexShader);
    glAttachShader(m_Program, fragmentShader);
    glLinkProgram(m_Program);
    glValidateProgram(m_Program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

Shader::~Shader() {
}

void Shader::use() {
    glUseProgram(m_Program);
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
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
