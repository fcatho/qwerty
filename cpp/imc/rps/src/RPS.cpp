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
	auto computer = std::make_shared<ComputerPlayer>("computer");

	RPSApp rps(human, computer, writer);

	writer->write("RPS game - Enter different from P, R, S to finish the game\n\n");
	rps.run();
	rps.show_score();

	return 0;
}
