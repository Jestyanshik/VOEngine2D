#include <vopch.h>
#include "VOEngine.h"


class Game : public Entrypoint {
	void onStart() {
		VO_INFO("Hello\n");
		VO_ASSERT(-1);
	}
	void onUpdate() {
		running = false;
	}
};


int main() { 
	Game game;
	game.run();
}