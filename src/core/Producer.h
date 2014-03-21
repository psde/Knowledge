#pragma once

#include <memory>

class DequeBuffer;

class IProducer
{
protected:
	std::shared_ptr<DequeBuffer> _buffer;

public:
	IProducer(DequeBuffer* buffer)
	: _buffer(buffer)
	{ 
	}

	std::shared_ptr<DequeBuffer> getBuffer()
	{
		return _buffer;
	}

	virtual void run() = 0;
};

class Producer : public IProducer
{
public:
	Producer();
	
	void run();
};