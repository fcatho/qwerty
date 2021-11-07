#ifndef RPSAPP_HPP
#define RPSAPP_HPP

#include "IPlayer.hpp"
#include "IWriter.hpp"
#include <memory>

class RPSApp
{
public:
	RPSApp(std::shared_ptr<IPlayer> playerA, std::shared_ptr<IPlayer> playerB, std::shared_ptr<IWriter> writer);
	virtual ~RPSApp() {}

	void run();

private:
	std::shared_ptr<IPlayer> judge(const char X, const char Y);
	bool valid_symbol(const char symbol);

	std::shared_ptr<IPlayer> playerA_;
	std::shared_ptr<IPlayer> playerB_;
	std::shared_ptr<IWriter> writer_;
};

#endif //RPSAPP_HPP
