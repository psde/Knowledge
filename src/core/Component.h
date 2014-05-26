#pragma once

#include <mutex>

class Component
{
private:
	std::mutex _shutdownMutex;
	bool _running;

protected:
	virtual void run(){};
	virtual void internalShutdown();

public:
	Component();
	~Component();

	void start();
	void shutdown();

	virtual void onStart() = 0;
	virtual void onShutdown() = 0;
};
