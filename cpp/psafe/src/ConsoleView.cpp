#include "ConsoleView.hpp"
#include <iostream>

void ConsoleIO::write(const std::string & data)
{
	std::cout << data;
}

std::string ConsoleIO::read()
{
	std::string data;
	std::getline(std::cin, data);
	return data;
}

ConsoleView::ConsoleView()
	: io_(std::make_shared<ConsoleIO>())
{
}

bool ConsoleView::keep_going()
{
	while (1)
	{
		io_->write("\n\n\nGuessing game!!!\n\n\n");
		io_->write("Think about an animal...\n\n");
		io_->write("C - Continue\nX - Exit\n");

		std::string ans = io_->read();

		if (ans == "C" || ans == "c")
		{
			return true;
		}
		else if (ans == "X" || ans == "x")
		{
			io_->write("See you later!\n");
			return false;
		}
		io_->write("\nSorry, invalid option... Try again, please\n");
	}
}

bool ConsoleView::ask_yes_no(const std::string & question)
{
	std::string ans;
	while (1)
	{
		io_->write(question + " (Y/N) ");
		ans = io_->read();
		if (ans == "Y" || ans == "y")
		{
			return true;
		}
		else if (ans == "N" || ans == "n")
		{
			return false;
		}
		io_->write("\nInvalid choice\n");
	}
}

bool ConsoleView::try_answer(const std::string & entity)
{
	return ask_yes_no("Is the animal you thought a " + entity + "?");
}

std::string ConsoleView::ask_entity()
{
	io_->write("What was the animal you thought about? ");
	return io_->read();
}

std::string ConsoleView::ask_property(const std::string & current_entity, const std::string & new_entity)
{
	io_->write("What does a " + new_entity + " do, that a " + current_entity + " does not? ");
	return io_->read();
}

void ConsoleView::win()
{
	io_->write("\n\nI win!!!\n");
}

bool ConsoleView::check_property(const std::string & property)
{
	return ask_yes_no("Does the animal you thought " + property + "?");
}

