#pragma once

#include <memory>

class DequeBuffer;

class Producer
{
private:
	std::shared_ptr<DequeBuffer> _buffer;
public:
	Producer();

	std::shared_ptr<DequeBuffer> getBuffer();

	void run();
};