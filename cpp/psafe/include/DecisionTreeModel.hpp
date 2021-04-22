#ifndef DECISION_TREE_MODEL
#define DECISION_TREE_MODEL

#include "ModelInterface.hpp"

class DecisionTreeModel : public ModelInterface
{
public:
	DecisionTreeModel();
	void init(const std::string & ability, const std::string & left_entity, const std::string & right_entity) override;
	void add(std::shared_ptr<DecisionNode> current, const std::string & entity, const std::string & ability) override;
	std::shared_ptr<DecisionNode> root() override;

private:
	void add_left(std::shared_ptr<DecisionNode> current, std::shared_ptr<DecisionNode> child);
	void add_right(std::shared_ptr<DecisionNode> current, std::shared_ptr<DecisionNode> child);

};



#endif // DECISION_TREE_MODEL
