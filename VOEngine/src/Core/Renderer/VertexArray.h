#pragma once

namespace VOEngine {
	class VertexArray {
	public:
		VertexArray() {};
		~VertexArray();
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
		void Bind();
		void Unbind();
		void SubmitAttach();
	protected:
		uint32_t CreateVertexArray();
		void CreateVertexBuffer();
		void CreateIndexBuffer();
		void VertexBufferSubData(const void* data, size_t size, size_t offset);
		void IndexBufferSubData(const void* data, size_t size, size_t offset);
		uint32_t m_ID = 0;
		uint32_t m_VertexBufferID = 0, m_IndexBufferID = 0;
	};
}