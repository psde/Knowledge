#pragma once

#include <deque>
#include <thread>
#include <mutex>

class DequeBuffer
{
private:
	std::deque<int> _deque;
	std::mutex _readMutex;
	std::mutex _writeMutex;

public:
	DequeBuffer();

	void add(int i);

	int get();
};