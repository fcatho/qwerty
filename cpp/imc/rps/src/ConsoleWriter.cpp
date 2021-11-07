#include "ConsoleWriter.hpp"
#include <iostream>

void ConsoleWriter::write(const std::string & data)
{
	std::cout << data << std::flush;
}

