#include "Data.h"
#include "DequeBuffer.h"

DequeBuffer::DequeBuffer()
{

}

void DequeBuffer::add(std::unique_ptr<Data> i)
{
	std::lock_guard<std::mutex> guard(_writeMutex);
	_deque.push_back(std::move(i));
}

std::unique_ptr<Data> DequeBuffer::get()
{
	std::lock_guard<std::mutex> guard(_readMutex);

	while(true)
	{
		std::lock_guard<std::mutex> guard(_writeMutex);
		if(_deque.size() > 0)
			break;
	}

	auto data = std::move(_deque.front());
	_deque.pop_front();
	return std::move(data);
}