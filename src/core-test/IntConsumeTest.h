#pragma once

#include <core/Producer.h>
#include <core/Consumer.h>
#include <core/DequePool.h>
#include <core/ConsumerProducer.h>

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

class Int42Producer : public Producer<IntData>
{
public:
	Int42Producer()
	: Producer<IntData>(10)
	{
	}

	std::unique_ptr<IntData> produce(std::unique_ptr<IntData> data)
	{
		data->setInt(42);
		std::cout << this << " producing " << data->getInt() << std::endl;
		return std::move(data);
	}
};

class MultiplyIntBy2 : public ConsumerProducer<IntData, IntData>
{
public:
	MultiplyIntBy2(std::shared_ptr<Producer<IntData>> producer, size_t maxQueueSize)
	: ConsumerProducer(producer, maxQueueSize)
	{
	}

	std::unique_ptr<IntData> process(std::unique_ptr<IntData> inData, std::unique_ptr<IntData> outData)
	{
		int i = inData->getInt();
		recycleData(std::move(inData));

		outData->setInt(i * 2);
		return std::move(outData);
	}
};

class IntOutput : public Consumer<IntData>
{
public:
	IntOutput(std::shared_ptr<Producer<IntData> > producer)
	: Consumer<IntData>(producer)
	{
	}

	void consume(std::unique_ptr<IntData> data)
	{
		std::cout << this << " consumed " << data->getInt() << std::endl;
		recycleData(std::move(data));
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
};
