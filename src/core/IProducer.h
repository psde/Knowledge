#pragma once

#include <memory>

class DequePool;

class IProducer
{
protected:
	std::shared_ptr<DequePool> _buffer;

public:
	IProducer(unsigned int maxQueueSize, std::shared_ptr<IDataFactory> factory);

	std::shared_ptr<DequePool> getBuffer();

	virtual void run() = 0;
};
