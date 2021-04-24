#ifndef CONSOLE_VIEW
#define CONSOLE_VIEW

#include "ViewInterface.hpp"
#include <memory>

class ConsoleIO : public IOInterface
{
public:
	void write(const std::string & data) override;
	std::string read() override;
};


class ConsoleView : public ViewInterface
{
public:
	ConsoleView();
	bool keep_going() override;
	bool try_answer(const std::string & entity) override;
	std::string ask_entity() override;
	std::string ask_property(const std::string & current_entity, const std::string & new_entity) override;
	void win() override;
	bool check_property(const std::string & property) override;

private:
	bool ask_yes_no(const std::string & question);

protected:
	std::shared_ptr<IOInterface> io_;
};

#endif // CONSOLE_VIEW

