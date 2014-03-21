#include <iostream>
#include "DequeBuffer.h"
#include "Producer.h"

Producer::Producer()
: _buffer(new DequeBuffer())
{
}

std::shared_ptr<DequeBuffer> Producer::getBuffer()
{
	return _buffer;
}

void Producer::run()
{
	while(true)
	{
		std::unique_ptr<IntData> i(new IntData(42));
		std::cout << this << " producing " << i->getInt() << std::endl;
		_buffer->add(std::move(i));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}