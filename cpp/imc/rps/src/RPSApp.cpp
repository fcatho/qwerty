#include "RPSApp.hpp"
#include <unordered_map>
#include <unordered_set>
#include <iostream>


RPSApp::RPSApp(std::shared_ptr<IPlayer> playerA, std::shared_ptr<IPlayer> playerB, std::shared_ptr<IWriter> writer)
	: playerA_(playerA)
	, playerB_(playerB)
	, writer_(writer)
{
}

void RPSApp::run()
{
	while (1)
	{
		char symbolA = playerA_->play();
		if (!valid_symbol(symbolA))
		{
			break;
		}

		char symbolB = playerB_->play();
		if (!valid_symbol(symbolB))
		{
			break;
		}

		writer_->write(std::string(&symbolA, 1) + " vs " + std::string(&symbolB, 1) + "\n");
		auto winner = judge(symbolA, symbolB);
		if (winner)
		{
			writer_->write(winner->id() + " win\n\n");
		}
		else
		{
			writer_->write("draw\n\n");
		}
	}
}

std::shared_ptr<IPlayer> RPSApp::judge(const char symbolA, const char symbolB)
{
	static std::unordered_map<std::string, std::shared_ptr<IPlayer>> winner_map {
		{"PP", nullptr},
		{"PR", playerA_},
		{"PS", playerB_},
		{"RP", playerB_},
		{"RR", nullptr},
		{"RS", playerA_},
		{"SP", playerA_},
		{"SR", playerB_},
		{"SS", nullptr}};

	std::string key = std::string(&symbolA, 1) + std::string(&symbolB, 1);
	return winner_map.find(key)->second;
}

bool RPSApp::valid_symbol(const char symbol)
{
	static const std::unordered_set<char> options = {'P', 'R', 'S'};
	return options.find(symbol) != options.end();
}
