#ifndef COMPUTERPLAYER_HPP
#define COMPUTERPLAYER_HPP

#include "IPlayer.hpp"

class ComputerPlayer : public IPlayer
{
public:
	ComputerPlayer();
	char play() override;
	const std::string & id() override;

private:
	const std::string id_;
};

#endif // COMPUTERPLAYER_HPP
