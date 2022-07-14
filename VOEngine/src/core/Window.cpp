#include "vopch.h"
#include "Window.h"

void VOEngine::Window::detectMonitor() {
	//TODO
}

void VOEngine::Window::createWindow() {
	glfwWindowHint(GLFW_RESIZABLE, m_Resizable);
	glfwWindowHint(GLFW_DECORATED, m_Decorated);
	glfwWindowHint(GLFW_FOCUSED, m_Focused);
	glfwWindowHint(GLFW_AUTO_ICONIFY, m_AutoIconify);
	glfwWindowHint(GLFW_MAXIMIZED, m_Maximized);
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		VO_CORE_CRITICAL("Couldn't initialize GLAD");
	}
	else
	{
		VO_CORE_INFO("[INFO] GLAD initialized\n");
	}
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

}

void VOEngine::Window::setWindowMode(int wm){
	if (wm == WindowModes::fullscreen) {
		glfwSetWindowMonitor(m_Window, m_PrimaryMonitor, 0, 0, m_Mode->width, m_Mode->height, m_Mode->refreshRate);
		//changeSize(m_Mode->width, m_Mode->height);
	}
	if (wm == WindowModes::borderless) {
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, 0);
		glfwSetWindowMonitor(m_Window, NULL, 0, 0, m_Mode->width, m_Mode->height, m_Mode->refreshRate);
	}
	if (wm == WindowModes::windowed) {
		glfwSetWindowAttrib(m_Window, GLFW_DECORATED, 1);
		glfwSetWindowMonitor(m_Window, NULL, (m_Mode->width - m_Width)/2 ,(m_Mode->height - m_Height)/2, m_Width, m_Height, NULL);

	}
}

bool VOEngine::Window::isKeyPressed(VOEngine::KeyCode key) {
	int state = glfwGetKey(m_Window, key);
	if (state == GLFW_PRESS)
	{
		return true;
	}
	else {
		return false;
	}
}

void VOEngine::Window::testFunc() {
	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	ImGui::Checkbox("Another Window", &show_another_window);

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(m_Window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_Window);
}

void VOEngine::Window::setIcon(const char* path) {
	//TODO
}

void VOEngine::Window::requestAttention() {
	glfwRequestWindowAttention(m_Window);
}

void VOEngine::Window::changeSize(int width, int height) {
	m_Width = width;
	m_Height = height;
	glfwSetWindowSize(m_Window, width, height);
}

void VOEngine::Window::changeTitle(const char* title) {
	glfwSetWindowTitle(m_Window, title);
}

void VOEngine::Window::update() {
	glfwSwapBuffers(m_Window);
}