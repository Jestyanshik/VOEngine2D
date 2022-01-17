#include "vopch.h"
#include "Entrypoint.h"
#include "Performance.h"


void Entrypoint::beforeStart() {
	timeit();
	VOEngine::Log::Init();
}

void Entrypoint::onStart() {

}

void Entrypoint::onUpdate() {}

void Entrypoint::onTerminate() {}

void Entrypoint::run() { 
	beforeStart();
	onStart(); 
	while (running) {
		onUpdate();
	}
	onTerminate();
}
