#pragma once

#include <memory>
#include <iostream>

class Producer;

// Needed?!
#include "Producer.h"
#include "DequeBuffer.h"

class IConsumer
{
private:

public:
	virtual void run() = 0;
};

class Consumer : public IConsumer
{
private:
	std::shared_ptr<IProducer> _producer;
public:
	Consumer(std::shared_ptr<IProducer> producer);

	void run();
};


class ConsumerProducer : public IConsumer, public IProducer
{
private:
	std::shared_ptr<IProducer> _producer;

public:
	ConsumerProducer(std::shared_ptr<IProducer> producer)
	: IProducer(new DequeBuffer(10))
	, _producer(producer)
	{

	}

	void run()
	{
		while (true)
		{
			Data* i = _producer->getBuffer()->get().release();
			IntData* test = dynamic_cast<IntData*>(i);

			std::unique_ptr<IntData> test2(new IntData(test->getInt() * 2));
			std::cout << this << " producing multiplied " << test2->getInt() << std::endl;
			_buffer->add(std::move(test2));
		}
	}
};