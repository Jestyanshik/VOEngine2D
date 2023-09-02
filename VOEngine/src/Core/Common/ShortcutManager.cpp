#include "vopch.h"
#include "ShortcutManager.h"

VOEngine::ShortcutManager::ShortcutManager(std::shared_ptr<Window> window): m_Window(window) {

}

VOEngine::ShortcutManager::~ShortcutManager() {

}

void VOEngine::ShortcutManager::AddShortcut(KeyCode key, std::function<void(void)> callback) {
	
}

void VOEngine::ShortcutManager::DispatchShorcuts() {
	
}

