#include <iostream>
#include "Data.h"
#include "DequePool.h"

DequePool::DequePool(unsigned int maxQueueSize, std::shared_ptr<DataFactory> factory)
: _maxQueueSize(maxQueueSize)
, _factory(factory)
{

}

void DequePool::enque(std::unique_ptr<Data> data)
{
	std::lock_guard<std::mutex> guard(_writeMutex);
	_deque.push_back(std::move(data));

	while (_deque.size() > _maxQueueSize)
	{
		std::cout << "Too much elements, poping front" << std::endl;
		_pool.push_back(std::move(_deque.front()));
		_deque.pop_front();
	}
	std::cout << "Pool size: " << _pool.size() << std::endl;
}

std::unique_ptr<Data> DequePool::deque()
{
	std::lock_guard<std::mutex> guard(_writeMutex);
	if (_pool.size() == 0)
	{
		std::cout << "Too few elements in pool, creating new one" << std::endl;
		return std::unique_ptr<Data>(_factory->createData());
	}

	std::unique_ptr<Data> ptr = std::move(_pool.back());
	_pool.pop_back();
	return ptr;
}

void DequePool::recycle(std::unique_ptr<Data> data)
{
	std::lock_guard<std::mutex> guard(_writeMutex);
	_pool.push_back(std::move(data));
}

std::unique_ptr<Data> DequePool::get()
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