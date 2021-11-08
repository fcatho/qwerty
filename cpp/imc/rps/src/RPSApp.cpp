#include "RPSApp.hpp"
#include <unordered_map>
#include <unordered_set>
#include <sstream>

RPSApp::RPSApp(std::shared_ptr<IPlayer> player_a, std::shared_ptr<IPlayer> player_b, std::shared_ptr<IWriter> writer)
	: player_a_{player_a}
	, player_b_{player_b}
	, writer_{writer}
	, winner_values_{player_a_, player_b_, nullptr}
{
}

bool RPSApp::read_from_players(PlayerOption & option_a, PlayerOption & option_b)
{
	return (
		(option_a = player_a_->play()) != PlayerOption::NONE &&
		(option_b = player_b_->play()) != PlayerOption::NONE);
}

void RPSApp::run()
{
	PlayerOption option_a, option_b;
	while (read_from_players(option_a, option_b))
	{
		auto winner = decide(option_a, option_b);
		if (winner)
		{
			winner->add_victory();
			writer_->write(winner->id() + " win\n\n");
		}
		else
		{
			writer_->write("draw\n\n");
		}
	}
}

void RPSApp::show_score() const
{
	writer_->write("Score:\n" +
		player_a_->id() + " " + std::to_string(player_a_->score()) + "\n vs \n" +
		player_b_->id() + " " + std::to_string(player_b_->score()) + "\n");
}

std::shared_ptr<IPlayer> RPSApp::decide(const PlayerOption option_a, const PlayerOption option_b)
{
	writer_->write(std::string(1, static_cast<char>(option_a)) +
			" vs " + std::string(1, static_cast<char>(option_b)) + "\n");

	auto key = [](const PlayerOption option_a, const PlayerOption option_b)
		{ return static_cast<char>(option_a) << 8 | static_cast<char>(option_b); };

	static std::unordered_map<uint16_t, size_t> winner_map {
		{key(PlayerOption::PAPER, PlayerOption::PAPER), 2},
		{key(PlayerOption::PAPER, PlayerOption::ROCK), 0},
		{key(PlayerOption::PAPER, PlayerOption::SCISSORS), 1},
		{key(PlayerOption::ROCK, PlayerOption::PAPER), 1},
		{key(PlayerOption::ROCK, PlayerOption::ROCK), 2},
		{key(PlayerOption::ROCK, PlayerOption::SCISSORS), 0},
		{key(PlayerOption::SCISSORS, PlayerOption::PAPER), 0},
		{key(PlayerOption::SCISSORS, PlayerOption::ROCK), 1},
		{key(PlayerOption::SCISSORS, PlayerOption::SCISSORS), 2}};


	uint16_t target = key(option_a, option_b);
	return winner_values_[winner_map.find(target)->second];
}

