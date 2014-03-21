#include <thread>

#include "Producer.h"
#include "Consumer.h"
#include "DequeBuffer.h"

int main()
{
	std::shared_ptr<Producer> producer(new Producer());
	std::shared_ptr<ConsumerProducer> consumerProducer(new ConsumerProducer(producer));
	std::shared_ptr<Consumer> consumer(new Consumer(consumerProducer));

	std::thread t0(&Producer::run, producer);
	std::thread t1(&ConsumerProducer::run, consumerProducer);
	std::thread t2(&Consumer::run, consumer);

	t0.join();

	return 0;
}