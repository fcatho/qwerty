#include "ConsoleView.hpp"
#include <iostream>

bool ConsoleView::keep_going()
{
	while (1)
	{
		std::cout << "\n\n\nGuessing game!!!\n\n\n";
		std::cout << "Think about an animal...\n\n";
		std::cout << "C - Continue\nX - Exit" << std::endl;

		std::string ans;
		//std::cin >> ans;
		std::getline(std::cin, ans);

		if (ans == "C" || ans == "c")
		{
			return true;
		}
		else if (ans == "X" || ans == "x")
		{
			std::cout << "See you later!\n";
			return false;
		}
		std::cout << "\nSorry, invalid option... Try again, please\n";
	}
}

bool ConsoleView::ask_yes_no(const std::string & question)
{
	std::string ans;
	while (1)
	{
		std::cout << question << " (Y/N) ";
		//std::cin >> ans;
		std::getline(std::cin, ans);
		if (ans == "Y" || ans == "y")
		{
			return true;
		}
		else if (ans == "N" || ans == "n")
		{
			return false;
		}
		std::cout << "\nInvalid choice\n";
	}
}

bool ConsoleView::try_answer(const std::string & entity)
{
	return ask_yes_no("Is the animal you thought a " + entity + "?");
}

std::string ConsoleView::ask_entity()
{
	std::string ans;
	std::cout << "What was the animal you thought about? ";
	std::getline(std::cin, ans);
	return ans;
}

std::string ConsoleView::ask_ability(const std::string & current_entity, const std::string & new_entity)
{
	std::string ans;
	std::cout << "What does a " + new_entity + " do, that a " + current_entity + " does not?";
	std::getline(std::cin, ans);
	return ans;
}

void ConsoleView::win()
{
	std::cout << "I win!!!\n";
}

bool ConsoleView::check_ability(const std::string & ability)
{
	return ask_yes_no("Does the animal you thought " + ability + "?");
}

