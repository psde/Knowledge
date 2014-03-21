#include <iostream>
#include "DequeBuffer.h"
#include "Data.h"
#include "Producer.h"
#include "Consumer.h"

Consumer::Consumer(std::shared_ptr<Producer> producer)
: _producer(producer)
{
}

void Consumer::run()
{
	while(true)
	{
		Data* i = _producer->getBuffer()->get().release();
		IntData* test = dynamic_cast<IntData*>(i);
		std::cout << this << " consumed " << test->getInt() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}	