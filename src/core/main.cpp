#include <thread>

#include "Producer.h"
#include "Consumer.h"
#include "DequeBuffer.h"

int main()
{
	std::shared_ptr<DequeBuffer> foo(new DequeBuffer());

	std::thread t0(&Consumer::run, new Consumer(foo));
	std::thread t1(&Consumer::run, new Consumer(foo));
	std::thread t2(&Producer::run, new Producer(foo));
	t2.join();
	t1.join();

	return 0;
}