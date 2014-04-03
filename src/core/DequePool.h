#pragma once

#include <deque>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include <iostream>

template<class T>
class Producer;

template<class T>
class DequePool
{
private:
	std::vector<std::unique_ptr<T> > _pool;
	std::deque<std::unique_ptr<T> > _deque;
	std::mutex _readMutex;
	std::mutex _writeMutex;
	Producer<T>* _producer;

	size_t _maxQueueSize;
	
	void trim()
	{
		if (_maxQueueSize <= 0)
			return;

		while (_deque.size() > _maxQueueSize)
		{
			std::cout << "Too much elements, poping front" << std::endl;
			_pool.push_back(std::move(_deque.front()));
			_deque.pop_front();
		}

		std::cout << "Pool size: " << _pool.size() << std::endl;
	}

public:
	DequePool(size_t maxQueueSize, Producer<T>* producer)
	: _maxQueueSize(maxQueueSize)
	, _producer(producer)
	{

	}

	void enque(std::unique_ptr<T> data)
	{
		std::lock_guard<std::mutex> guard(_writeMutex);
		_deque.push_back(std::move(data));
		trim();
	}

	std::unique_ptr<T> deque()
	{
		std::lock_guard<std::mutex> guard(_writeMutex);

		trim();

		if (_pool.size() == 0)
		{
			std::cout << "Too few elements in pool, creating new one" << std::endl;
			return _producer->createNew();
		}

		std::unique_ptr<T> ptr = std::move(_pool.back());
		_pool.pop_back();
		return ptr;
	}

	void recycle(std::unique_ptr<T> data)
	{
		std::lock_guard<std::mutex> guard(_writeMutex);
		_pool.push_back(std::move(data));
	}

	std::unique_ptr<T> get()
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
};
