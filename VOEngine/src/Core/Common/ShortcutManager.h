#pragma once
#include "Core/Window/Window.h"
#include "Core/Common/Consts.h"

namespace VOEngine {
	class ShortcutManager {
	public:
		ShortcutManager(std::shared_ptr<Window> window);
		~ShortcutManager();

		void AddShortcut(KeyCode key, std::function<void(void)> callback);
		void DispatchShorcuts();

	private:
		std::shared_ptr<Window> m_Window;
		
	};
}
