#include <thread>

#include "IntConsumeTest.h"

int main()
{
	std::shared_ptr<Int42Producer> int42Producer(new Int42Producer());
	std::shared_ptr<MultiplyIntBy2> consumerProducer(new MultiplyIntBy2(int42Producer, 10));
	std::shared_ptr<IntOutput> intOutput(new IntOutput(consumerProducer));

	std::thread t0(&Int42Producer::start, int42Producer);
	std::thread t1(&MultiplyIntBy2::start, consumerProducer);
	std::thread t2(&IntOutput::start, intOutput);
	
	std::this_thread::sleep_for(std::chrono::seconds(10));

	intOutput->shutdown();
	consumerProducer->shutdown();
	int42Producer->shutdown();

	t0.join();
	t1.join();
	t2.join();

	return 0;
}