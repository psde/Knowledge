#include "DequeBuffer.h"

DequeBuffer::DequeBuffer()
{

}

void DequeBuffer::add(int i)
{
	std::lock_guard<std::mutex> guard(_writeMutex);
	_deque.push_back(i);
}

int DequeBuffer::get()
{
	std::lock_guard<std::mutex> guard(_readMutex);

	while(true)
	{
		std::lock_guard<std::mutex> guard(_writeMutex);
		if(_deque.size() > 0)
			break;
	}

	int i = _deque.front();
	_deque.pop_front();
	return i;
}