#include <iostream>
#include "DequeBuffer.h"
#include "Consumer.h"

Consumer::Consumer(std::shared_ptr<DequeBuffer> foo)
: _foo(foo)
{
}

void Consumer::run()
{
	while(true)
	{
		int i = _foo->get();
		std::cout << this << " consumed " << i << std::endl;
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}	