#include "Component.h"

Component::Component()
: _running(false)
{

}

Component::~Component()
{

}

void Component::start()
{
	_running = true;
	onStart();
	while (_running)
	{
		std::lock_guard<std::mutex> guard(_shutdownMutex);
		this->run();
	}
	internalShutdown();
	onShutdown();
}

void Component::shutdown()
{
	std::lock_guard<std::mutex> guard(_shutdownMutex);
	_running = false;
}

void Component::internalShutdown()
{

}

void Component::onStart()
{

}

void Component::onShutdown()
{

}
