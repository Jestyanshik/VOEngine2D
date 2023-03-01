#include "vopch.h"
#include "OpenGLVertexArray.h"

VOEngine::OpenGLVertexArray::~OpenGLVertexArray() {
	glDeleteVertexArrays(1, &m_ID);
	glDeleteBuffers(1, &m_VertexBuffer);
	glDeleteBuffers(1, &m_IndexBuffer);
}

void VOEngine::OpenGLVertexArray::Bind() {
	glBindVertexArray(m_ID);
}

uint32_t VOEngine::OpenGLVertexArray::AttachVertexBuffer(void* data, size_t size) {
	uint32_t VertexBuffer;
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	return VertexBuffer;
}

uint32_t VOEngine::OpenGLVertexArray::AttachIndexBuffer(void* data, size_t size) {
	uint32_t IndexBuffer;
	glGenBuffers(1, &IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	return IndexBuffer;
}

uint32_t VOEngine::OpenGLVertexArray::GenerateVertexArray() {
	uint32_t id;
	glGenVertexArrays(1, &id);
	return id;
}

void VOEngine::OpenGLVertexArray::SubmitAttach() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VOEngine::OpenGLVertexArray::Unbind() {
	glBindVertexArray(0);
}
