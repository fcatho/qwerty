#ifndef COMPUTERPLAYER_HPP
#define COMPUTERPLAYER_HPP

#include "IPlayer.hpp"

class ComputerPlayer : public IPlayer
{
public:
	ComputerPlayer(const std::string & id);

	/*!
	 * @brief Return a valid value from enum PlayerOption randomly choosen
	 */
	PlayerOption play() override;
};

#endif // COMPUTERPLAYER_HPP

