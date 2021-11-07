#include "ComputerPlayer.hpp"
#include <cstdlib>
#include <ctime>

ComputerPlayer::ComputerPlayer(const std::string & id)
	: IPlayer(id)
{
}

char ComputerPlayer::play()
{
	std::srand(std::time(nullptr));
	static const char options[3] = {'R', 'P', 'S'};

	return options[std::rand() % sizeof(options)];
}

