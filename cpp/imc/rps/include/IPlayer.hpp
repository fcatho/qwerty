#ifndef IPLAYER_HPP
#define IPLAYER_HPP

#include <string>
#include <unordered_set>

enum class PlayerOption : char
{
	PAPER = 'P',
	ROCK = 'R',
	SCISSORS = 'S',
	NONE = 'X',
};


class IPlayer
{
public:
	IPlayer(const std::string & id);
	virtual ~IPlayer();

	/*!
	 * @brief Retrive identifier
	 * @return id_ as const reference
	 */
	virtual const std::string & id() const;

	/*!
	 * @brief Add +1 to current score_
	 */
	virtual void add_victory();

	/*!
	 * @brief Return score value
	 */
	virtual uint32_t score() const;

	/*!
	 * @brief Check if given char is a valid representation of enum PlayerOptions
	 * @param symbol
	 * @return true if valid, false otherwise
	 */
	bool valid(const char symbol);

	/*!
	 * @brief Retrieve choosen option from player
	 * @return A value from enum PlayerOption
	 */
	virtual PlayerOption play() = 0;

protected:
	static const std::unordered_set<PlayerOption> VALID_PLAYER_OPTIONS;
	const std::string id_;
	uint32_t score_;
};

#endif // IPLAYER_HPP

