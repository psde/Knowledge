#include <iostream>
#include <thread>

class Foo
{
public:
	Foo()
	{

	}

	void hello()
	{
		std::cout << "Hello from class!" << std::endl;
	}
};


void fooClass(Foo *f)
{
	f->hello();
}

void hello()
{
	std::cout << "Hello!" << std::endl;
}

int main()
{
	std::thread t1(hello); 
	t1.join();

	std::thread t2(fooClass, new Foo());
	t2.join();

	return 0;
}