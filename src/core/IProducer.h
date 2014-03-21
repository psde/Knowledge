#pragma once

#include <memory>

class DequePool;

class IProducer
{
protected:
	std::shared_ptr<DequePool> _buffer;

public:
	IProducer(DequePool* buffer)
	: _buffer(buffer)
	{ 
	}

	std::shared_ptr<DequePool> getBuffer()
	{
		return _buffer;
	}

	virtual void run() = 0;
};
