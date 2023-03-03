#pragma once

namespace VOEngine {
	class VertexArray {
	public:
		VertexArray() {};
		void AttachBuffers(const std::vector<float>& VBO, const std::vector<uint32_t>& IBO, size_t VBOoffset, size_t IBOoffset) {
			m_VertexBuffer.insert(m_VertexBuffer.begin(), VBO.begin(), VBO.end());
			m_IndexBuffer.insert(m_IndexBuffer.begin(), IBO.begin(), IBO.end());
			VertexBufferSubData(m_VertexBuffer.data(), m_VertexBuffer.size() * sizeof(float), VBOoffset * sizeof(float));
			IndexBufferSubData(m_IndexBuffer.data(), m_IndexBuffer.size() * sizeof(uint32_t), IBOoffset * sizeof(uint32_t));
		}
		void Create() {
			m_ID = m_ID == 0 ? CreateVertexArray() : m_ID;
			CreateVertexBuffer();
			CreateIndexBuffer();
			SubmitAttach();
		}
		size_t GetIndexCount() { return m_IndexBuffer.size(); };
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SubmitAttach() = 0;
	protected:
		virtual uint32_t CreateVertexArray() = 0;
		virtual void CreateVertexBuffer() = 0;
		virtual void CreateIndexBuffer() = 0;
		virtual void VertexBufferSubData(const void* data, size_t size, size_t offset) = 0;
		virtual void IndexBufferSubData(const void* data, size_t size, size_t offset) = 0;
		std::vector<float> m_VertexBuffer{};
		std::vector<uint32_t> m_IndexBuffer{};
		uint32_t m_ID = 0;
		uint32_t m_VertexBufferID = 0, m_IndexBufferID = 0;
	};
}