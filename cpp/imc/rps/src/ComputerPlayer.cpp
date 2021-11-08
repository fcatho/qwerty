#include "ComputerPlayer.hpp"
#include <cstdlib>
#include <ctime>

ComputerPlayer::ComputerPlayer(const std::string & id)
	: IPlayer(id)
{
}

PlayerOption ComputerPlayer::play()
{
	std::srand(std::time(nullptr));
	auto pos = std::rand() % IPlayer::VALID_PLAYER_OPTIONS.size();
	auto it = IPlayer::VALID_PLAYER_OPTIONS.cbegin();
	std::advance(it, pos);
	return static_cast<PlayerOption>(*it);
}

