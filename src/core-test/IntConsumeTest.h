#pragma once

#include <core/IData.h>
#include <core/IProducer.h>
#include <core/IConsumer.h>
#include <core/DequePool.h>

// IntData
class IntData : public IData
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
	: IData()
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

class IntDataFactory : public IDataFactory
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
	: IProducer(10, std::shared_ptr<IDataFactory>(new IntDataFactory()))
	{
	}

	void run()
	{
		while (true)
		{
			std::unique_ptr<IntData> intData = static_unique_ptr_cast<IntData, IData>(_buffer->deque());
			intData->setInt(42);
			std::cout << this << " producing " << intData->getInt() << std::endl;
			_buffer->enque(std::move(intData));
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
};

class MultiplyIntBy2 : public IConsumer, public IProducer
{
private:
	std::shared_ptr<IProducer> _producer;

public:
	MultiplyIntBy2(std::shared_ptr<IProducer> producer)
	: IProducer(10, std::shared_ptr<IDataFactory>(new IntDataFactory()))
	, _producer(producer)
	{

	}

	void run()
	{
		while (true)
		{
			std::unique_ptr<IntData> intData = static_unique_ptr_cast<IntData, IData>(_producer->getBuffer()->get());
			int i = intData->getInt();
			_producer->getBuffer()->recycle(std::move(intData));

			std::unique_ptr<IntData> intData2 = static_unique_ptr_cast<IntData, IData>(_buffer->deque());
			intData2->setInt(i * 2);
			std::cout << this << " producing multiplied " << intData2->getInt() << std::endl;
			_buffer->enque(std::move(intData2));
		}
	}
};

class AddTwoInts : public IConsumer, public IProducer
{
private:
	std::shared_ptr<IProducer> _producer1, _producer2;

public:
	AddTwoInts(std::shared_ptr<IProducer> producer1, std::shared_ptr<IProducer> producer2)
	: IProducer(10, std::shared_ptr<IDataFactory>(new IntDataFactory()))
	, _producer1(producer1)
	, _producer2(producer2)
	{

	}

	void run()
	{
		while (true)
		{
			std::unique_ptr<IntData> intData1 = static_unique_ptr_cast<IntData, IData>(_producer1->getBuffer()->get());
			int i1 = intData1->getInt();
			_producer1->getBuffer()->recycle(std::move(intData1));

			std::unique_ptr<IntData> intData2 = static_unique_ptr_cast<IntData, IData>(_producer2->getBuffer()->get());
			int i2 = intData2->getInt();
			_producer2->getBuffer()->recycle(std::move(intData2));

			std::unique_ptr<IntData> intData = static_unique_ptr_cast<IntData, IData>(_buffer->deque());
			intData->setInt(i1 + i2);
			std::cout << this << " adding " << i1 << " and " << i2 << ": " << intData->getInt() << std::endl;
			_buffer->enque(std::move(intData));
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
			std::unique_ptr<IntData> intData = static_unique_ptr_cast<IntData, IData>(_producer->getBuffer()->get());
			std::cout << this << " consumed " << intData->getInt() << std::endl;
			_producer->getBuffer()->recycle(std::move(intData));
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
	}
};
