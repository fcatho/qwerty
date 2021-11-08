#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer(const std::string & id, std::shared_ptr<IReader> reader, std::shared_ptr<IWriter> writer)
	: IPlayer(id)
	, reader_(reader)
	, writer_(writer)
{
}

PlayerOption HumanPlayer::play()
{
	writer_->write("Choose P, R or S: ");
	char input = std::toupper(reader_->read().front());
	if (valid(input))
	{
		return static_cast<PlayerOption>(input);
	}

	return PlayerOption::NONE;
}

