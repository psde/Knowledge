#include <thread>

#include "Producer.h"
#include "Consumer.h"
#include "DequeBuffer.h"

int main()
{
	std::shared_ptr<Producer> producer(new Producer());

	std::thread t0(&Producer::run, producer);
	std::thread t1(&Consumer::run, new Consumer(producer));
	std::thread t2(&Consumer::run, new Consumer(producer));
	std::thread t3(&Consumer::run, new Consumer(producer));
	std::thread t4(&Consumer::run, new Consumer(producer));
	std::thread t5(&Consumer::run, new Consumer(producer));

	t0.join();

	return 0;
}