#pragma once

#include <memory>

class DequeBuffer;

class Consumer
{
private:
	std::shared_ptr<DequeBuffer> _foo;
public:
	Consumer(std::shared_ptr<DequeBuffer> foo);

	void run();
};