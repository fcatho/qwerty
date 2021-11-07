#ifndef IWRITER_HPP
#define IWRITER_HPP

#include <string>

class IWriter
{
public:
	virtual ~IWriter() {}
	virtual void write(const std::string & message) = 0;
};

#endif // IWRITER_HPP

