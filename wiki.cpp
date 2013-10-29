#include <cstring>
#include <iostream>

#include <string.h>

int object_index = 1;

class Foo
{
public:
	Foo (void) :
		number(object_index++),
		message (nullptr)
	{
		std::cout << "default constructor " << this << "\n";
	}

	Foo (const char *msg) :
		number(object_index++)
	{
		if (msg)
			message = strdup (msg);
		else
			message = nullptr;
		std::cout << "named constructor " << this << "\n";
	}

	Foo (const Foo& other) :
		number(object_index++)
	{
		if (other.message)
			message = strdup (other.message);
		else
			message = nullptr;
		std::cout << "copy constructor " << this << "\n";
	}

	Foo (Foo&& other) :
		Foo()
	{
		swap(*this, other);
		std::cout << "move constructor " << this << "\n";
	}

	virtual ~Foo()
	{
		std::cout << "destructor " << this << "\n";
		free (message);
	}

	Foo& operator= (const Foo& other)
	{
		Foo temporary (other);

		std::swap (message, temporary.message);

		std::cout << "copy assignment " << this << "\n";
		return *this;
	}

	Foo& operator= (Foo&& other)
	{
		std::swap (message, other.message);

		std::cout << "move assignment " << this << "\n";
		return *this;
	}

private:
	friend void swap(Foo& first, Foo& second)
	{
		std::cout << "swap " << first << " and " << second << "\n";
		std::swap(first.message, second.message);
	}

	friend std::ostream& operator<< (std::ostream& os, const Foo* foo)
	{
		if (foo)
			return operator<< (os, *foo);
		else
			return os;
	}

	friend std::ostream& operator<< (std::ostream& os, const Foo& foo)
	{
		os << "Object F" << foo.number << ": ";
		if (foo.message)
			os << "\"" << foo.message << "\"";
		else
			os << "[null]";
		return os;
	}


	int number;
	char* message;
};

Foo function (void)
{
	return Foo("damson");
}

int main()
{
	std::cout << "\nf1\n";
	const Foo f1 ("apple");

	std::cout << "\nf2\n";
	Foo f2 = f1;

	std::cout << "\nf3\n";
	Foo f3 = "cherry";

	std::cout << "\nf4\n";
	Foo f4 = Foo();

	std::cout << "\nrval\n";
	f3 = function();

	std::cout << "\nstd::swap\n";
	std::swap (f2, f3);

	std::cout << "\nobject swap\n";
	swap (f2, f3);

	std::cout << "\nend\n";
	return 0;
}

