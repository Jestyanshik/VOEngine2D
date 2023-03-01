#pragma once

namespace VOEngine {
	class VertexArray {
	public:
		VertexArray() {};
		void AttachBuffers(const std::vector<float>& VBO, const std::vector<uint32_t>& IBO) {
			m_ID = GenerateVertexArray();
			Bind();
			m_VertexBuffer = AttachVertexBuffer((void*)VBO.data(), VBO.size() * sizeof(float));
			m_IndexBuffer = AttachIndexBuffer((void*)IBO.data(), IBO.size() * sizeof(uint32_t));
			SubmitAttach();
			Unbind();
		}
		//virtual ~VertexArray() = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	protected:
		virtual uint32_t GenerateVertexArray() = 0;
		virtual uint32_t AttachVertexBuffer(void* data, size_t size) = 0;
		virtual uint32_t AttachIndexBuffer(void* data, size_t size) = 0;
		virtual void SubmitAttach() = 0;
		uint32_t m_ID;
		uint32_t m_VertexBuffer, m_IndexBuffer;
	};
}