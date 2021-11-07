#include "RPSApp.hpp"
#include "ConsoleReader.hpp"
#include "ConsoleWriter.hpp"
#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"

int main()
{
	auto reader = std::make_shared<ConsoleReader>();
	auto writer = std::make_shared<ConsoleWriter>();
	auto human = std::make_shared<HumanPlayer>("you", reader, writer);
	auto computer = std::make_shared<ComputerPlayer>("spock");
	RPSApp rps(human, computer, writer);

	rps.run();

	return 0;
}
