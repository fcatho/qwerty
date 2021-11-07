#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer(std::shared_ptr<IReader> reader, std::shared_ptr<IWriter> writer)
	: reader_(reader)
	, writer_(writer)
	, id_("human")
{
}

char HumanPlayer::play()
{
	writer_->write("Choose P, R or S: ");
	return std::toupper(reader_->read().front());
}

const std::string & HumanPlayer::id()
{
	return id_;
}

