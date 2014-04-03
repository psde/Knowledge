#pragma once

#include <memory>
#include <mutex>

#include "Component.h"
#include "DequePool.h"

template<class T>
class Producer : public virtual Component
{
friend class DequePool<T>;

private:

protected:
	std::shared_ptr<DequePool<T>> _buffer;

	virtual std::unique_ptr<T> createNew()
	{
		return std::unique_ptr<T>(new T());
	}

	virtual void run()
	{
		_buffer->enque(this->produce(_buffer->deque()));
	}

	virtual void internalShutdown()
	{
		_buffer->shutdown();
	}

public:
	Producer(unsigned int maxQueueSize)
	: _buffer(new DequePool<T>(maxQueueSize, this))
	{
	}

	std::shared_ptr<DequePool<T> > getBuffer()
	{
		return _buffer;
	}

	virtual std::unique_ptr<T> produce(std::unique_ptr<T> data) = 0;
};
