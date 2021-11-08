#include "ComputerPlayer.hpp"

using distr_type = std::uniform_int_distribution<std::mt19937::result_type>;

ComputerPlayer::ComputerPlayer(const std::string & id)
	: IPlayer(id)
	, rng_(dev_())
	, distribution_(distr_type(0, 10))
{
}

PlayerOption ComputerPlayer::play()
{
	auto pos = distribution_(rng_) % IPlayer::VALID_PLAYER_OPTIONS.size();
	auto it = IPlayer::VALID_PLAYER_OPTIONS.cbegin();
	std::advance(it, pos);
	return static_cast<PlayerOption>(*it);
}

