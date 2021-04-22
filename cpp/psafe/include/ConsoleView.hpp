#ifndef CONSOLE_VIEW
#define CONSOLE_VIEW

#include "ViewInterface.hpp"

class ConsoleView : public ViewInterface
{
public:
	bool keep_going() override;
	bool try_answer(const std::string & entity) override;
	std::string ask_entity() override;
	std::string ask_ability(const std::string & current_entity, const std::string & new_entity) override;
	void win() override;
	bool check_ability(const std::string & ability) override;

private:
	bool ask_yes_no(const std::string & question);
};

#endif // CONSOLE_VIEW

