#pragma once

#include <core/Data.h>
#include <core/IProducer.h>
#include <core/IConsumer.h>
#include <core/DequePool.h>

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

	void setInt(int i)
	{
		_i = i;
	}
};

class IntDataFactory : public DataFactory
{
public:
	IntData* createData()
	{
		return new IntData();
	}
};


class Int42Producer : public IProducer
{
public:
	Int42Producer()
	: IProducer(new DequePool(10, std::shared_ptr<DataFactory>(new IntDataFactory())))
	{
	}

	void run()
	{
		while (true)
		{
			std::unique_ptr<IntData> intData = static_unique_ptr_cast<IntData, Data>(_buffer->deque());
			intData->setInt(42);
			std::cout << this << " producing " << intData->getInt() << std::endl;
			_buffer->enque(std::move(intData));
			std::this_thread::sleep_for(std::chrono::milliseconds(150));
		}
	}
};

class MultiplyIntBy2 : public IConsumer, public IProducer
{
private:
	std::shared_ptr<IProducer> _producer;

public:
	MultiplyIntBy2(std::shared_ptr<IProducer> producer)
	: IProducer(new DequePool(10, std::shared_ptr<DataFactory>(new IntDataFactory())))
	, _producer(producer)
	{

	}

	void run()
	{
		while (true)
		{
			std::unique_ptr<IntData> intData = static_unique_ptr_cast<IntData, Data>(_producer->getBuffer()->get());
			int i = intData->getInt();
			_producer->getBuffer()->recycle(std::move(intData));

			std::unique_ptr<IntData> intData2 = static_unique_ptr_cast<IntData, Data>(_buffer->deque());
			intData2->setInt(i);
			std::cout << this << " producing multiplied " << intData2->getInt() << std::endl;
			_buffer->enque(std::move(intData2));
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
			std::unique_ptr<IntData> intData = static_unique_ptr_cast<IntData, Data>(_producer->getBuffer()->get());
			std::cout << this << " consumed " << intData->getInt() << std::endl;
			_producer->getBuffer()->recycle(std::move(intData));
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}

};
