#include <vopch.h>
#include "VOEngine.h"

int main() {
	VOEngine::Log::Init();
	VO_INFO("Hello\n");
	VO_ASSERT(-1);
	return 0;
}