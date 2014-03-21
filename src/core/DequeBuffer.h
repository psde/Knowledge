#pragma once

#include <deque>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>

#include "Data.h"

class DequeBuffer
{
private:
	std::vector<std::unique_ptr<Data> > pool;
	std::deque<std::unique_ptr<Data> > _deque;
	std::mutex _readMutex;
	std::mutex _writeMutex;

public:
	DequeBuffer();

	void add(std::unique_ptr<Data> i);

	std::unique_ptr<Data> get();
};