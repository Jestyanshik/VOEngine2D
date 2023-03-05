#pragma once

namespace VOEngine {
	class VertexArray {
	public:
		VertexArray() {};
		void AttachVertexBuffer(const std::vector<float>& VBO, size_t offset) {
			VertexBufferSubData(VBO.data(), VBO.size() * sizeof(float), offset * sizeof(float));
		}
		void AttachIndexBuffer(const std::vector<uint32_t>& IBO, size_t offset) {
			IndexCount += IBO.size();
			IndexBufferSubData(IBO.data(), IBO.size() * sizeof(uint32_t), offset * sizeof(uint32_t));
		}
		void Create() {
			m_ID = m_ID == 0 ? CreateVertexArray() : m_ID;
			CreateVertexBuffer();
			CreateIndexBuffer();
			SubmitAttach();
		}
		size_t IndexCount = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SubmitAttach() = 0;
	protected:
		virtual uint32_t CreateVertexArray() = 0;
		virtual void CreateVertexBuffer() = 0;
		virtual void CreateIndexBuffer() = 0;
		virtual void VertexBufferSubData(const void* data, size_t size, size_t offset) = 0;
		virtual void IndexBufferSubData(const void* data, size_t size, size_t offset) = 0;
		uint32_t m_ID = 0;
		uint32_t m_VertexBufferID = 0, m_IndexBufferID = 0;
	};
}