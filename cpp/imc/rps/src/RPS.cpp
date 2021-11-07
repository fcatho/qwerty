#include "RPSApp.hpp"
#include "ConsoleReader.hpp"
#include "ConsoleWriter.hpp"
#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"

int main()
{
	auto reader = std::make_shared<ConsoleReader>();
	auto writer = std::make_shared<ConsoleWriter>();
	auto human = std::make_shared<HumanPlayer>(reader, writer);
	auto computer = std::make_shared<ComputerPlayer>();
	RPSApp prs(human, computer, writer);

	prs.run();

	return 0;
}
