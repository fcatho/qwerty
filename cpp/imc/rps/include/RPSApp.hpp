#ifndef RPSAPP_HPP
#define RPSAPP_HPP

#include "IPlayer.hpp"
#include "IWriter.hpp"
#include <memory>

class RPSApp
{
public:
	RPSApp(std::shared_ptr<IPlayer> player_a, std::shared_ptr<IPlayer> player_b, std::shared_ptr<IWriter> writer);
	virtual ~RPSApp() {}

	/*
	 * @brief Keep reading from player_a  and player_b until invalid input. If both are valid entries, then
	 * determine the winner or draw, updat ethe score and keep going.
	 */
	void run();

	/*
	 * @brief Prints using writer_ a message with the score values
	 */
	void show_score() const;

private:
	std::shared_ptr<IPlayer> decide(const PlayerOption symbolA, const PlayerOption symbolB);
	bool read_from_players(PlayerOption & option_a, PlayerOption & option_b);

	std::shared_ptr<IPlayer> player_a_;
	std::shared_ptr<IPlayer> player_b_;
	std::shared_ptr<IWriter> writer_;
	std::shared_ptr<IPlayer> winner_values_[3]; //>Helper array to select the winner based on index
};

#endif //RPSAPP_HPP
