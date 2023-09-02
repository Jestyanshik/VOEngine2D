#include "vopch.h"
#include "ShortcutManager.h"

VOEngine::ShortcutManager::ShortcutManager(std::shared_ptr<Window> window): m_Window(window) {

}

VOEngine::ShortcutManager::~ShortcutManager() {

}

void VOEngine::ShortcutManager::AddShortcut(KeyCode key, std::function<void(void)> callback) {
	m_ShortCuts.emplace(key, callback);	
}

void VOEngine::ShortcutManager::DispatchShorcuts() {
	for (auto it = m_ShortCuts.begin(); it != m_ShortCuts.end(); it++) {
		if (m_Window->IsKeyPressed(it->first))
			it->second();
	}
}

