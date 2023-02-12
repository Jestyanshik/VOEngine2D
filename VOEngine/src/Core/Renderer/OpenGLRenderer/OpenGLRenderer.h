#pragma once
#include "../Renderer.h"
#include "Shaders/Shader.h"
#include "Core/ResourceManager.h"


namespace VOEngine { 
	class OpenGLRenderer : public Renderer {
	public:
		void doFill(color color) override;
		void doDrawRectangle() override {};
		void doDrawLine() override {};
		void doDrawText() override {};
		void doDrawCircle() override {};
		void doDrawArc() override {};
		void doDrawBezier() override  {};
		void render() override;

		const char* getVersion();
		OpenGLRenderer();

	};
}
