#include <vopch.h>
#include "VOEngine.h"


class Game : public Entrypoint {
public:
	VOEngine::Window Window = VOEngine::Window(1280, 720, "My Game", true, true, true, false, false);
	void onStart() {
	}
	void onUpdate() {
		Window.testFunc();
		if (Window.isKeyPressed(VOEngine::Key::Escape)) {
			running = false;
		}
		if (Window.isKeyPressed(VOEngine::Key::F)) {
			Window.setWindowMode(WindowModes::fullscreen);
		}
		if (Window.isKeyPressed(VOEngine::Key::W)) {
			Window.setWindowMode(WindowModes::windowed);
		}
		if (Window.isKeyPressed(VOEngine::Key::B)) {
			Window.setWindowMode(WindowModes::borderless);
		}
		if (Window.isKeyPressed(VOEngine::Key::S)) {
			Window.requestAttention();
		}

		Window.update();
	}
	void onTerminate() {
		
	}
};


int main() { 
	Game game;
	game.run();
}