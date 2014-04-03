#pragma once

#include <mutex>

class Component
{
private:
	std::mutex _shutdownMutex;
	bool _running;

protected:
	virtual void run(){};

public:
	Component();
	~Component();

	void start();
	void shutdown();

	virtual void onStart(); 
	virtual void onShutdown();
};
