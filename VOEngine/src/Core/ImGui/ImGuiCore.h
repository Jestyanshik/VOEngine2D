#pragma once
#include "Core/ImGui/ImGuiBackend/imgui_impl_opengl3.h"
#include "Core/ImGui/ImGuiBackend/imgui_impl_glfw.h"
#include "GLFW/glfw3.h"

namespace ImGuiWrapper {
	
	void NewFrame();
	void DockSpace();
	void EndFrame();

	void QuickWindow(const std::string& name, const std::string& info);


}
