#ifndef COMPUTERPLAYER_HPP
#define COMPUTERPLAYER_HPP

#include "IPlayer.hpp"
#include <random>

class ComputerPlayer : public IPlayer
{
public:
	ComputerPlayer(const std::string & id);

	/*!
	 * @brief Return a valid value from enum PlayerOption randomly choosen
	 */
	PlayerOption play() override;

private:
	std::random_device dev_;
	std::mt19937 rng_;
	std::uniform_int_distribution<std::mt19937::result_type> distribution_;
};

#endif // COMPUTERPLAYER_HPP

