#include "vopch.h"
#include "OpenGLVertexArray.h"

VOEngine::OpenGLVertexArray::~OpenGLVertexArray() {
	glDeleteVertexArrays(1, &m_ID);
	glDeleteBuffers(1, &m_VertexBufferID);
	glDeleteBuffers(1, &m_IndexBufferID);
}

void VOEngine::OpenGLVertexArray::Bind() {
	glBindVertexArray(m_ID);
}

void VOEngine::OpenGLVertexArray::CreateVertexBuffer() {
	glCreateBuffers(1, &m_VertexBufferID);
	glNamedBufferData(m_VertexBufferID, sizeof(float) * 9 * 4096, nullptr, GL_DYNAMIC_DRAW);
}

void VOEngine::OpenGLVertexArray::CreateIndexBuffer() {
	glCreateBuffers(1, &m_IndexBufferID);
	glNamedBufferData(m_IndexBufferID, sizeof(float) * 4096, nullptr, GL_DYNAMIC_DRAW);
}

uint32_t VOEngine::OpenGLVertexArray::CreateVertexArray() {
	glCreateVertexArrays(1, &m_ID);
	return m_ID;
}

void VOEngine::OpenGLVertexArray::SubmitAttach() {
	glEnableVertexArrayAttrib(m_ID, 0);
	glVertexArrayAttribBinding(m_ID, 0, 0);
	glVertexArrayAttribFormat(m_ID, 0, 3, GL_FLOAT, GL_FALSE, 0);

	glEnableVertexArrayAttrib(m_ID, 1);
	glVertexArrayAttribBinding(m_ID, 1, 0);
	glVertexArrayAttribFormat(m_ID, 1, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	glEnableVertexArrayAttrib(m_ID, 2);
	glVertexArrayAttribBinding(m_ID, 2, 0);
	glVertexArrayAttribFormat(m_ID, 2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float));

	glVertexArrayVertexBuffer(m_ID, 0, m_VertexBufferID, 0, 9 * sizeof(float));
	glVertexArrayElementBuffer(m_ID, m_IndexBufferID);
}

void VOEngine::OpenGLVertexArray::VertexBufferSubData(const void* data, size_t size, size_t offset) {
	glNamedBufferSubData(m_VertexBufferID, offset, size, data);
}

void VOEngine::OpenGLVertexArray::IndexBufferSubData(const void* data, size_t size, size_t offset) {
	glNamedBufferSubData(m_IndexBufferID, offset, size, data);
}

void VOEngine::OpenGLVertexArray::Unbind() {
	glBindVertexArray(0);
}
