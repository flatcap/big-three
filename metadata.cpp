#include <utility>
#include <iostream>
#include <vector>
#include <string>

class MetaData
{
public:
	MetaData (void) :
		_name(),
		_size(0)
	{
		std::cout << "default constructor (0,\"\")\n";
	}

	MetaData (int size, const std::string& name) :
		_name(name),
		_size(size)
	{
		std::cout << "values constructor (" << _size << ",\"" << _name << "\")\n";
	}

	virtual ~MetaData (void)
	{
		std::cout << "default destructor (" << _size << ",\"" << _name << "\")\n";
	}

	MetaData (const MetaData& other) :
		_name(other._name),
		_size(other._size)
	{
		std::cout << "copy constructor (" << _size << ",\"" << _name << "\")\n";
	}

	MetaData (MetaData&& other) :
		_name(std::move(other._name)),
		_size(other._size)
	{
		std::cout << "move constructor (" << _size << ",\"" << _name << "\")\n";
	}

	MetaData & operator= (const MetaData& other)
	{
		_name = other._name;
		_size = other._size;
		std::cout << "copy assignment (" << _size << ",\"" << _name << "\")\n";
		return *this;
	}

	MetaData & operator= (MetaData&& other)
	{
		_name = std::move(other._name);
		_size = other._size;
		std::cout << "move assignment (" << _size << ",\"" << _name << "\")\n";
		return *this;
	}

	std::string getName() const
	{
		return _name;
	}

	int getSize() const
	{
		return _size;
	}

private:
	std::string _name;
	int _size;
};


MetaData function (MetaData &object)
{
	std::cout << "function\n";
	return object;
}

int main()
{
	std::cout << "\nm1\n";
	MetaData m1;

	std::cout << "\nm2\n";
	MetaData m2 (42, "hello");

	std::cout << "\nm3\n";
	MetaData m3 (m2);

	std::cout << "\nm4\n";
	MetaData m4;
	m4 = m2;

	std::cout << "\nm5\n";
	MetaData m5 (std::move(m2));

	std::cout << "\nm6\n";
	MetaData m6;
	m6 = MetaData(999, "police");

	std::cout << "\nswap\n";
	std::swap(m5,m6);

	std::cout << "\n";

	return 0;
}


