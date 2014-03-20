#pragma once

#include <memory>

class DequeBuffer;

class Producer
{
private:
	std::shared_ptr<DequeBuffer> _foo;
public:
	Producer(std::shared_ptr<DequeBuffer> foo);

	void run();
};