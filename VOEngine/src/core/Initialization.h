#pragma once 
#include "GLFW/glfw3.h"
#include "ResourceManager.h"

namespace VOEngine {
	static void Init() {
		Log::Init();
		VO_CORE_ASSERT(glfwInit());
		ResourceManager::Init();
	};

	static void Cleanup() {
		ResourceManager::Cleanup();
	}
};