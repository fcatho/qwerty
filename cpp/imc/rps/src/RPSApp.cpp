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
		char ansA = playerA_->play();
		char ansB = playerB_->play();
		if (!valid_answer(ansA) || !valid_answer(ansB))
		{
			break;
		}

		writer_->write(std::string(&ansA, 1) + " vs " + std::string(&ansB, 1) + "\n");
		auto winner = judge(ansA, ansB);
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

std::shared_ptr<IPlayer> RPSApp::judge(const char ansA, const char ansB)
{
	static const std::unordered_map<std::string, std::shared_ptr<IPlayer>> winner_map {
		{"PP", nullptr},
		{"PR", playerA_},
		{"PS", playerB_},
		{"RP", playerB_},
		{"RR", nullptr},
		{"RS", playerA_},
		{"SP", playerA_},
		{"SR", playerB_},
		{"SS", nullptr}};

	return winner_map.find(std::string(&ansA) + std::string(&ansB))->second;
}

bool RPSApp::valid_answer(const char ans)
{
	static const std::unordered_set<char> options = {'P', 'R', 'S'};
	return options.find(ans) != options.end();
}
