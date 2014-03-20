#include <iostream>
#include "DequeBuffer.h"
#include "Producer.h"

Producer::Producer(std::shared_ptr<DequeBuffer> foo)
: _foo(foo)
{
}

void Producer::run()
{
	while(true)
	{
		int i = 42;
		std::cout << this << " producing " << i << std::endl;
		_foo->add(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}