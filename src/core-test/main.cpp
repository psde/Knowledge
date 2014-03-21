#include <thread>

#include "IntConsumeTest.h"

int main()
{
	std::shared_ptr<Int42Producer> producer(new Int42Producer());
	std::shared_ptr<MultiplyIntBy2> consumerProducer(new MultiplyIntBy2(producer));
	std::shared_ptr<IntConsumer> consumer(new IntConsumer(consumerProducer));

	std::thread t0(&Int42Producer::run, producer);
	std::thread t1(&MultiplyIntBy2::run, consumerProducer);
	std::thread t2(&IntConsumer::run, consumer);

	t0.join();

	return 0;
}