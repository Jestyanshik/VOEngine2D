#include "vopch.h"
#include "SceneRenderer.h"
#include "Core/ResourceManager.h"

VOEngine::SceneRenderer::SceneRenderer() {
	m_Renderer = std::make_unique<Renderer>();
	m_Framebuffer = std::make_shared<Framebuffer>(800,600, "Scene");
	auto eventNotifier = ResourceManager::GetInstance().GetEventNotifier();
	eventNotifier->Subscribe(EventType::Resize, EventCallback{[this](void* info) {OnResize(info);}, "SceneRenderer"});
	eventNotifier->Subscribe(EventType::RenderUpdate, EventCallback{ [this](void*) {UpdateBuffers();}, "SceneRenderer" });
}

void VOEngine::SceneRenderer::SetScene(std::shared_ptr<Scene> scene) {
	if (m_Scene == scene) {
		return;
	}
	m_Scene = scene;

	UpdateBuffers();
}

void VOEngine::SceneRenderer::Render() {	
	if (m_Scene == nullptr) 
		return;

	m_Framebuffer->BeginFrame();
	
	m_Renderer->Clear({ 0,0,0,1 });
	
	for (const auto& it : m_Scene->GetRenderUnits()) 
		it.second->UpdateVertices();
	
	for (const auto& VAO : m_VertexArrays) 
		m_Renderer->DrawElements(VAO.get(), m_IndicesCount);
	
	m_Framebuffer->EndFrame();
}

void VOEngine::SceneRenderer::OnResize(void* eventInfo) {
	auto info = *(ResizeEventInfo*)eventInfo;
	m_Renderer->SetViewport(info.Size);
	m_Framebuffer->Resize(info.Size);
}

void VOEngine::SceneRenderer::UpdateBuffers() {
	if (m_Scene == nullptr) {
		return;
	}
	if (m_IndicesCount != 0) {
		for (const auto& it : m_Scene->GetRenderUnits()) {
			if (it.second->VAO == nullptr) {
				auto vao = CreateUnitVAO(it.second);
				it.second->VAO = vao;
				it.second->Offset = m_IndicesCount / 6;
				it.second->UpdateVertices();
				auto indices = it.second->UpdateIndices(m_IndicesCount / 6);
				vao->AttachIndexBuffer(indices, (m_IndicesCount));
				m_IndicesCount += it.second->IndicesCount;
			}
		}
		return;
	}

	m_IndicesCount = 0;
	m_VertexArrays.clear();
	std::unordered_set<UnitTypes> types;
	for (const auto& it : m_Scene->GetRenderUnits()) {
		std::shared_ptr<Unit> unit = it.second;
		auto vao = CreateUnitVAO(unit);
		if (auto search = types.find(unit->Type); search == types.end()) {
			m_VertexArrays.push_back(vao);
		}
		types.emplace(unit->Type);

		unit->Offset = m_IndicesCount / 6;
		unit->UpdateVertices();
		auto indices = unit->UpdateIndices(m_IndicesCount / 6);
		vao->AttachIndexBuffer(indices, m_IndicesCount);
		m_IndicesCount += unit->IndicesCount;
	}
}

std::shared_ptr<VOEngine::VertexArray> VOEngine::SceneRenderer::CreateUnitVAO(std::shared_ptr<Unit> unit) {
	if (unit->VAO == nullptr) {
		unit->VAO = std::shared_ptr<VertexArray>(m_Builder.Create(unit->Type));
	}
	return unit->VAO;
}