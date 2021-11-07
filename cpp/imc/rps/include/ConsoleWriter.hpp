#ifndef CONSOLEWRITER_HPP
#define CONSOLEWRITER_HPP

#include "IWriter.hpp"

class ConsoleWriter : public IWriter
{
public:
	void write(const std::string & data) override;
};

#endif // CONSOLEWRITER_HPP

