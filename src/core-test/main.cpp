#include <thread>

#include "IntConsumeTest.h"

int main()
{
	std::shared_ptr<Int42Producer> producer42(new Int42Producer());
	std::shared_ptr<MultiplyIntBy2> consumerProducer(new MultiplyIntBy2(producer42));
	std::shared_ptr<AddTwoInts> consumerProducerAdd(new AddTwoInts(consumerProducer, producer42));
	std::shared_ptr<IntConsumer> consumer(new IntConsumer(consumerProducerAdd));

	std::thread t0(&Int42Producer::run, producer42);
	std::thread t1(&MultiplyIntBy2::run, consumerProducer);
	std::thread t2(&AddTwoInts::run, consumerProducerAdd);
	std::thread t3(&IntConsumer::run, consumer);

	t0.join();

	return 0;
}