#pragma once

#include <memory>

class Producer;

class Consumer
{
private:
	std::shared_ptr<Producer> _producer;
public:
	Consumer(std::shared_ptr<Producer> producer);

	void run();
};