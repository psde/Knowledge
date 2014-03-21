#include <iostream>
#include "DequePool.h"
#include "IProducer.h"

IProducer::IProducer(unsigned int maxQueueSize, std::shared_ptr<IDataFactory> factory)
: _buffer(new DequePool(maxQueueSize, factory))
{
}

std::shared_ptr<DequePool> IProducer::getBuffer()
{
	return _buffer;
}
