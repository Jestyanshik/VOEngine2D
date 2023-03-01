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
		uint32_t AttachVertexBuffer(void* data, size_t size) override;
		uint32_t AttachIndexBuffer(void* data, size_t size) override;
		uint32_t GenerateVertexArray() override;
		void SubmitAttach() override;
	private:

	};
}


