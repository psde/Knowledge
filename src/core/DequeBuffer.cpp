#include <iostream>
#include "Data.h"
#include "DequeBuffer.h"

DequeBuffer::DequeBuffer(unsigned int maxQueueSize)
: _maxQueueSize(maxQueueSize)
{

}

void DequeBuffer::add(std::unique_ptr<Data> i)
{
	std::lock_guard<std::mutex> guard(_writeMutex);
	_deque.push_back(std::move(i));

	while (_deque.size() > _maxQueueSize)
	{
		std::cout << "Too much elements, poping front" << std::endl;
		_deque.pop_front();
	}
}

std::unique_ptr<Data> DequeBuffer::get()
{
	std::lock_guard<std::mutex> guard(_readMutex);

	while(true)
	{
		_writeMutex.lock();
		if(_deque.size() > 0)
			break;
		_writeMutex.unlock();
	}

	auto data = std::move(_deque.front());
	_deque.pop_front();
	_writeMutex.unlock();
	return std::move(data);
}