#pragma once

#include <core/IData.h>
#include <core/IProducer.h>
#include <core/IConsumer.h>
#include <core/DequePool.h>

// IntData
class IntData
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

class Int42Producer : public IProducer<IntData>
{
public:
	Int42Producer()
	: IProducer<IntData>(10)
	{
	}

	void run()
	{
		while (true)
		{
			std::unique_ptr<IntData> intData = _buffer->deque();
			intData->setInt(42);
			std::cout << this << " producing " << intData->getInt() << std::endl;
			_buffer->enque(std::move(intData));
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
};


class MultiplyIntBy2 : public IConsumer<IntData>, public IProducer<IntData>
{
public:
	MultiplyIntBy2(std::shared_ptr<IProducer<IntData> > producer)
	: IConsumer<IntData>(producer)
	, IProducer<IntData>(10)
	{
	}

	void run()
	{
		while (true)
		{
			std::unique_ptr<IntData> intData = getData();
			int i = intData->getInt();
			recycleData(std::move(intData));

			std::unique_ptr<IntData> intData2 = _buffer->deque();
			intData2->setInt(i * 2);
			std::cout << this << " producing multiplied " << intData2->getInt() << std::endl;
			_buffer->enque(std::move(intData2));
		}
	}
};

class AddTwoInts : public IProducer<IntData>
{
private:
	std::shared_ptr<IConsumer<IntData> > _consumer1, _consumer2;

public:
	AddTwoInts(std::shared_ptr<IProducer<IntData> > producer1, std::shared_ptr<IProducer<IntData> > producer2)
	: IProducer<IntData>(10)
	, _consumer1(new IConsumer<IntData>(producer1))
	, _consumer2(new IConsumer<IntData>(producer2))
	{
	}

	void run()
	{
		while (true)
		{
			std::unique_ptr<IntData> intData1 = _consumer1->getData();
			int i1 = intData1->getInt();
			_consumer1->recycleData(std::move(intData1));

			std::unique_ptr<IntData> intData2 = _consumer2->getData();
			int i2 = intData2->getInt();
			_consumer2->recycleData(std::move(intData2));

			std::unique_ptr<IntData> intData = _buffer->deque();
			intData->setInt(i1 + i2);
			std::cout << this << " adding " << i1 << " and " << i2 << ": " << intData->getInt() << std::endl;
			_buffer->enque(std::move(intData));
		}
	}
};

class IntConsumer : public IConsumer<IntData>
{
public:
	IntConsumer(std::shared_ptr<IProducer<IntData> > producer)
	: IConsumer<IntData>(producer)
	{
	}

	void run()
	{
		while (true)
		{
			std::unique_ptr<IntData> intData = getData();
			std::cout << this << " consumed " << intData->getInt() << std::endl;
			recycleData(std::move(intData));
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
	}
};
