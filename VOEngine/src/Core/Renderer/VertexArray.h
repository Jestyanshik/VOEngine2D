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
		void ClearVertexBuffer();
		void ClearIndexBuffer();
		void Clear();
		void Bind();
		void Unbind();
		void SubmitAttach();
	private:
		uint32_t CreateVertexArray();
		void CreateVertexBuffer();
		void CreateIndexBuffer();
		void VertexBufferSubData(const void* data, size_t size, size_t offset);
		void IndexBufferSubData(const void* data, size_t size, size_t offset);
		const size_t m_VertexBufferSize = sizeof(float) * 9 * 4096;
		const size_t m_IndexBufferSize = sizeof(uint32_t) * 4096;
		uint32_t m_ID = 0;
		uint32_t m_VertexBufferID = 0, m_IndexBufferID = 0;
	};

	class VertexArrayBuilder {
	public:
		VertexArrayBuilder() {};
		std::shared_ptr<VertexArray> Create(UnitTypes type);
	private:
		std::unordered_map<UnitTypes, std::shared_ptr<VertexArray>> m_VertexArrays{};

	};
}