#pragma once

#include <mutex>

template<class TConsume, class TProduce>
class ConsumerProducer : public Consumer<TConsume>, public Producer<TProduce>
{
private:
	std::unique_ptr<TProduce> data;

protected:
	virtual void run()
	{
		std::unique_ptr<TConsume> c = this->getData();
		if (c != nullptr)
			this->_buffer->enque(this->process(std::move(c), this->_buffer->deque()));
	}

	virtual void internalShutdown()
	{
		this->_buffer->shutdown();
	}

public:
	ConsumerProducer(std::shared_ptr<Producer<TProduce>> producer, size_t maxQueueSize)
	: Consumer<TConsume>(producer)
	, Producer<TProduce>(maxQueueSize)
	, data()
	{
	}

	std::unique_ptr<TProduce> produce(std::unique_ptr<TProduce> /*data*/)
	{
		return nullptr;
	}

	void consume(std::unique_ptr<TConsume> /*data*/)
	{

	}

	virtual std::unique_ptr<TProduce> process(std::unique_ptr<TConsume> inData, std::unique_ptr<TProduce> outData) = 0;
};
