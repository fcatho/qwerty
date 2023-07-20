#include <utility>
#include <iostream>
class resource {
	public:
		int x = 0;
};
class foo
{
	public:
		foo(const int value)
			: p{new resource{}}
		{ 
			p->x = value;
			std::cout << "ctor " << p->x << std::endl;
		}
		foo(const foo& other)
			: p{new resource{*(other.p)}}
		{
			std::cout << "copy ctor " << p->x << std::endl;
		}
		foo& operator=(const foo& other)
		{
			std::cout << "copy assignment operator " << p->x << std::endl;
			if (&other != this) {
				delete p;
				p = nullptr;
				p = new resource{*(other.p)};
			}
			return *this;
		}
		~foo()
		{

			if (p)
			{
				std::cout << "dtor " << p->x << std::endl;
			}
			delete p;
		}


        foo(foo&& other)
			: p{other.p}
		{
			std::cout << "move ctor " << p->x << std::endl;
			other.p = nullptr;
		}

		foo& operator=(foo&& other)
		{
			std::cout << "move assignment operator " << p->x << std::endl;
			if (&other != this) {
				delete p;
				p = other.p;
				other.p = nullptr;
			}
			return *this;
		}

		foo& operator+(const foo & other)
		{
			this->p->x += other.p->x;
			return *this;
		}
		resource* p;
};

foo get1()
{
	return std::move(foo(5));
}

foo get2()
{
	foo f1(10);
	return std::move(f1);
}

void bar(foo & f)
{
	foo f2 = std::move(f);
	foo f3(1);
	f3 = std::move(f2);
	//std::cout << "by ref bar: " << f2.p->x << std::endl;
}

//void bar(foo & f, int i = 0)
//{
//	std::cout << "bar: " << f.p->x << " i: " << i << std::endl;
//}

//int value = 5;
int main()
{
	//foo f1(1); //ctor
	//foo f2(f1);
	//foo f4 = f1 + f2; //copy ctor
	//f4 = f1 + f2; //copy ass operator
	//foo f5 = std::move(f1); //move ctor
	//f5 = std::move(f2); //move ass operator

	//bar(foo(1000));
	//bar(f1);
	//bar(std::move(f1));
	foo f1(10);// = get1();
	bar(f1);
	//foo f2 = get2();
	////std::cout << value << std::endl;
	//int value = value;
	//std::cout << value << std::endl;
	return 0;
}
