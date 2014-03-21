#pragma once

#include <deque>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>

#include "Data.h"

class DequePool
{
private:
	std::vector<std::unique_ptr<Data> > _pool;
	std::deque<std::unique_ptr<Data> > _deque;
	std::mutex _readMutex;
	std::mutex _writeMutex;

	std::shared_ptr<DataFactory> _factory;

	unsigned int _maxQueueSize;
	
public:
	DequePool(unsigned int maxQueueSize, std::shared_ptr<DataFactory> factory);

	void enque(std::unique_ptr<Data> data);
	std::unique_ptr<Data> deque();

	void recycle(std::unique_ptr<Data> data);
	std::unique_ptr<Data> get();
};