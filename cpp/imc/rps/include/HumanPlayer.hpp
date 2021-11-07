#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "IPlayer.hpp"
#include "IReader.hpp"
#include "IWriter.hpp"
#include <memory>

class HumanPlayer : public IPlayer
{
public:
	HumanPlayer(std::shared_ptr<IReader> reader, std::shared_ptr<IWriter> writer);
	char play() override;
	const std::string & id();

private:
	std::shared_ptr<IReader> reader_;
	std::shared_ptr<IWriter> writer_;
	const std::string id_;
};

#endif // HUMANPLAYER_HPP

