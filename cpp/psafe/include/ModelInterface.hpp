#ifndef MODEL_INTERFACE
#define MODEL_INTERFACE

#include <memory>
#include <vector>

struct DecisionNode
{
	enum DecisionNodeSide
	{
		LEFT,
		RIGHT
	};

	std::shared_ptr<DecisionNode> left;
	std::shared_ptr<DecisionNode> right;
	std::shared_ptr<DecisionNode> parent;
	std::string ability;
	std::string entity;
	DecisionNodeSide side;
};


class ModelInterface
{
public:
	virtual ~ModelInterface() {}
	virtual void init(const std::string & ability, const std::string & left_entity, const std::string & right_entity) = 0;
	virtual void add(std::shared_ptr<DecisionNode> current, const std::string & entity, const std::string & ability) = 0;
	virtual std::shared_ptr<DecisionNode> root() = 0;

protected:
	std::vector<std::shared_ptr<DecisionNode>> nodes_;
	std::shared_ptr<DecisionNode> root_;

};

#endif //MODEL_INTERFACE

