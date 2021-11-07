#ifndef IPLAYER_HPP
#define IPLAYER_HPP

#include <string>

class IPlayer
{
public:
	virtual ~IPlayer() {}
	virtual char play() = 0;
	virtual const std::string & id() = 0;
};

#endif // IPLAYER_HPP

