#include <iostream>
#include <algorithm>
#include <cstring>

class MyString
{
public:
	MyString (void) :
		str(nullptr)
	{
	}

	MyString (const char *init)
	{
		str = strdup (init);
	}

	MyString (const MyString &&rval)
	{
		swap(rval);
	}

	virtual ~MyString()
	{
		free (str);
	}

	MyString & operator = (MyString s)
	{
		s.swap (*this); // Non-throwing swap
		return *this;
	}

	void swap (MyString &s) throw () // Also see non-throwing swap idiom
	{
		std::swap(this->str, s.str);
	}

private:
	char * str;
};

MyString createMyString()
{
	return MyString("wibble");
}

int
main (int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	MyString createMyString();
	MyString s;
	s = createMyString();
}

