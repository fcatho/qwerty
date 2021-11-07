#include "ConsoleReader.hpp"
#include <iostream>

std::string ConsoleReader::read()
{
	std::string data;
	std::cin >> data;
	return data;
}

