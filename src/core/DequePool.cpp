#include <iostream>
#include "IData.h"
#include "DequePool.h"

DequePool::DequePool(unsigned int maxQueueSize, std::shared_ptr<IDataFactory> factory)
: _maxQueueSize(maxQueueSize)
, _factory(factory)
{

}

void DequePool::trim()
{
	while (_deque.size() > _maxQueueSize)
	{
		std::cout << "Too much elements, poping front" << std::endl;
		_pool.push_back(std::move(_deque.front()));
		_deque.pop_front();
	}

	std::cout << "Pool size: " << _pool.size() << std::endl;
}

void DequePool::enque(std::unique_ptr<IData> data)
{
	std::lock_guard<std::mutex> guard(_writeMutex);
	_deque.push_back(std::move(data));
	trim();
}

std::unique_ptr<IData> DequePool::deque()
{
	std::lock_guard<std::mutex> guard(_writeMutex);

	trim();

	if (_pool.size() == 0)
	{
		std::cout << "Too few elements in pool, creating new one" << std::endl;
		return std::unique_ptr<IData>(_factory->createData());
	}

	std::unique_ptr<IData> ptr = std::move(_pool.back());
	_pool.pop_back();
	return ptr;
}

void DequePool::recycle(std::unique_ptr<IData> data)
{
	std::lock_guard<std::mutex> guard(_writeMutex);
	_pool.push_back(std::move(data));
}

std::unique_ptr<IData> DequePool::get()
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