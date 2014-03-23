#pragma once

#include <memory>
#include <iostream>

#include "IProducer.h"

template<class T> 
class IConsumer
{
private:
	std::shared_ptr<IProducer<T> > _producer;

public:
	IConsumer(std::shared_ptr<IProducer<T> > producer)
	: _producer(producer)
	{

	}

	std::unique_ptr<T> getData()
	{
		std::unique_ptr<T> data = _producer->getBuffer()->get();
		return std::move(data);
	}

	void recycleData(std::unique_ptr<T> data)
	{
		_producer->getBuffer()->recycle(std::move(data));
	}
};
