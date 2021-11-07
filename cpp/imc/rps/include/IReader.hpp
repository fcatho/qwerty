#ifndef IREADER_HPP
#define IREADER_HPP

#include <string>

class IReader
{
public:
	virtual std::string read() = 0;
};

#endif // IREADER_HPP

