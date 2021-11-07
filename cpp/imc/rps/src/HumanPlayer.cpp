#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer(const std::string & id, std::shared_ptr<IReader> reader, std::shared_ptr<IWriter> writer)
	: IPlayer(id)
	, reader_(reader)
	, writer_(writer)
{
}

char HumanPlayer::play()
{
	writer_->write("Choose P, R or S: ");
	return std::toupper(reader_->read().front());
}

