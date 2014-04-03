#pragma once

#include <memory>
#include <iostream>

#include "Component.h"
#include "Producer.h"

template<class T> 
class Consumer : public virtual Component
{
private:
	std::shared_ptr<Producer<T> > _producer;

protected:
	virtual void run()
	{
		this->consume(getData());
	}

	std::unique_ptr<T> getData()
	{
		std::unique_ptr<T> data = _producer->getBuffer()->get();
		return std::move(data);
	}

public:
	Consumer(std::shared_ptr<Producer<T> > producer)
	: _producer(producer)
	{

	}

	void recycleData(std::unique_ptr<T> data)
	{
		_producer->getBuffer()->recycle(std::move(data));
	}

	virtual void consume(std::unique_ptr<T> data) = 0;
};
