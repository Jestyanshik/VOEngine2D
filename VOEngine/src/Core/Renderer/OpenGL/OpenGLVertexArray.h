#pragma once
#include "../VertexArray.h"

namespace VOEngine {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray() : VertexArray() {}
		~OpenGLVertexArray();
		void Bind() override;
		void Unbind() override;
	protected:
		void CreateVertexBuffer() override;
		void CreateIndexBuffer() override;
		uint32_t CreateVertexArray() override;
		void SubmitAttach() override;
		void VertexBufferSubData(const void* data, size_t size, size_t offset) override;
		void IndexBufferSubData(const void* data, size_t size, size_t offset) override;
	private:

	};
}


