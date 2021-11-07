#ifndef CONSOLEREADER_HPP
#define CONSOLEREADER_HPP

#include "IReader.hpp"

class ConsoleReader : public IReader
{
public:
	std::string read() override;
};

#endif //CONSOLEREADER_HPP
