#ifndef COMPUTERPLAYER_HPP
#define COMPUTERPLAYER_HPP

#include "IPlayer.hpp"

class ComputerPlayer : public IPlayer
{
public:
	ComputerPlayer(const std::string & id);
	char play() override;
};

#endif // COMPUTERPLAYER_HPP

