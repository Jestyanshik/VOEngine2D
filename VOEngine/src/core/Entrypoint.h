#pragma once
class Entrypoint {
public:
	bool running = true;
	

private:
	void beforeStart();
public:
	virtual void onStart();
	virtual void onUpdate();
	virtual void onTerminate();
    void run();
};

