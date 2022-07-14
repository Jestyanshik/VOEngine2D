#include "vopch.h"
#include "Entrypoint.h"
#include "Performance.h"
#include "GLFW/glfw3.h"

void Entrypoint::beforeStart() {

}


void Entrypoint::afterUpdate() {
	glfwPollEvents();
	
}

void Entrypoint::afterTerminate() {
	glfwTerminate();
}



void Entrypoint::run() { 
	beforeStart();
	onStart();
	while (running) {
		onUpdate();
		afterUpdate();
	}
	onTerminate();
	afterTerminate();
}
