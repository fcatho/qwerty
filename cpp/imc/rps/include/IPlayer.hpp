#ifndef IPLAYER_HPP
#define IPLAYER_HPP

#include <string>

class IPlayer
{
public:
	IPlayer(const std::string & id)
		: id_(id)
	{
	}

	virtual ~IPlayer()
	{
	}

	virtual const std::string & id() const
	{
		return id_;
	}

	virtual char play() = 0;

protected:
	const std::string id_;
};

#endif // IPLAYER_HPP

