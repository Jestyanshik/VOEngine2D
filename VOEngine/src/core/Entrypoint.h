#pragma once
class Entrypoint {
public:
	bool running = true;
	bool loggerInit = VOEngine::Log::Init();

private:
	void beforeStart();
	void afterUpdate();
	void afterTerminate();
public:
	virtual void onStart() {};
	virtual void onUpdate() {};
	virtual void onTerminate() {};
    void run();
};

