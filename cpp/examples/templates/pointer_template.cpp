#include <iostream>

template <class T>
class MyClass
{
public:
	virtual void MyFunction(const T & t)
	{
		std::cout << "MyFunction T& t " << t << std::endl;
	}
};

class MyDerivedClass : public MyClass<int *>
{
public:
	void MyFunction(int * const & i) override
	{
		std::cout << "MyFunction int * i " << *i << std::endl;
	}
};

int main()
{
	MyDerivedClass d;
	int j = 10;
	d.MyFunction(&j);
}

