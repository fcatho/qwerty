#ifndef HUMANPLAYER_HPP
#define HUMANPLAYER_HPP

#include "IPlayer.hpp"
#include "IReader.hpp"
#include "IWriter.hpp"
#include <memory>

class HumanPlayer : public IPlayer
{
public:
	HumanPlayer(const std::string & id, std::shared_ptr<IReader> reader, std::shared_ptr<IWriter> writer);
	char play() override;

private:
	std::shared_ptr<IReader> reader_;
	std::shared_ptr<IWriter> writer_;
};

#endif // HUMANPLAYER_HPP

