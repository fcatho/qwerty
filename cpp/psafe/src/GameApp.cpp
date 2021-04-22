#include "GamePresenter.hpp"
#include "DecisionTreeModel.hpp"
#include "ConsoleView.hpp"

int main()
{
	auto decision_tree = std::make_shared<DecisionTreeModel>();
	auto console = std::make_shared<ConsoleView>();
	GamePresenter game(decision_tree, console);

	game.run();

	return 0;
}
