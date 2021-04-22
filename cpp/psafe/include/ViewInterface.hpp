#ifndef VIEW_INTERFACE
#define VIEW_INTERFACE

#include <string>

class ViewInterface
{
public:
	virtual ~ViewInterface() {}
	virtual bool keep_going() = 0;
	virtual bool try_answer(const std::string & entity) = 0;
	virtual std::string ask_entity() = 0;
	virtual std::string ask_ability(const std::string & current_entity, const std::string & new_entity) = 0;
	virtual void win() = 0;
	virtual bool check_ability(const std::string & ability) = 0;
};

#endif //VIEW_INTERFACE
