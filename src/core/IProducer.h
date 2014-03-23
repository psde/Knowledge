#pragma once

#include <memory>

#include "DequePool.h"

template<class T>
class IProducer
{
protected:
	std::shared_ptr<DequePool<T> > _buffer;

public:
	IProducer(unsigned int maxQueueSize)
	: _buffer(new DequePool<T>(maxQueueSize))
	{
	}

	std::shared_ptr<DequePool<T> > getBuffer()
	{
		return _buffer;
	}

	virtual void run()
	{
		
	}
};
