#include "ComputerPlayer.hpp"
#include <cstdlib>
#include <ctime>

ComputerPlayer::ComputerPlayer()
	: id_("computer")
{
}

char ComputerPlayer::play()
{
	std::srand(std::time(nullptr));
	static const char options[3] = {'R', 'P', 'S'};

	return options[std::rand() % 3];
}

const std::string & ComputerPlayer::id()
{
	return id_;
}
