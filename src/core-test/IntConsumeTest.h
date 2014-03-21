#pragma once

#include <core/Data.h>
#include <core/IProducer.h>
#include <core/IConsumer.h>
#include <core/DequeBuffer.h>

// IntData
class IntData : public Data
{
private:
	int _i;

public:
	IntData()
	: _i(0)
	{}

	IntData(int i)
	: _i(i)
	{}

	IntData(const IntData& other)
	{
		_i = other._i;
	}

	IntData(IntData&& other)
	{
		_i = other._i;
	}

	int getInt()
	{
		return _i;
	}
};


class Int42Producer : public IProducer
{
public:
	Int42Producer()
	: IProducer(new DequeBuffer(10))
	{
	}

	void run()
	{
		while (true)
		{
			std::unique_ptr<IntData> i(new IntData(42));
			std::cout << this << " producing " << i->getInt() << std::endl;
			_buffer->add(std::move(i));
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	}
};

class IntMultiplier : public IConsumer, public IProducer
{
private:
	std::shared_ptr<IProducer> _producer;

public:
	IntMultiplier(std::shared_ptr<IProducer> producer)
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


class IntConsumer : public IConsumer
{
private:
	std::shared_ptr<IProducer> _producer;
public:
	IntConsumer(std::shared_ptr<IProducer> producer)
	: _producer(producer)
	{
	}

	void run()
	{
		while (true)
		{
			Data* i = _producer->getBuffer()->get().release();
			IntData* test = dynamic_cast<IntData*>(i);
			std::cout << this << " consumed " << test->getInt() << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}
	}

};
