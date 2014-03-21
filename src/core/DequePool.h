#pragma once

#include <deque>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>

#include "IData.h"

class DequePool
{
private:
	std::vector<std::unique_ptr<IData> > _pool;
	std::deque<std::unique_ptr<IData> > _deque;
	std::mutex _readMutex;
	std::mutex _writeMutex;

	std::shared_ptr<IDataFactory> _factory;

	size_t _maxQueueSize;
	
	void trim();

public:
	DequePool(size_t maxQueueSize, std::shared_ptr<IDataFactory> factory);

	void enque(std::unique_ptr<IData> data);
	std::unique_ptr<IData> deque();

	void recycle(std::unique_ptr<IData> data);
	std::unique_ptr<IData> get();
};