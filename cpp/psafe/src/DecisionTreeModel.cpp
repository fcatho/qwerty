#include "DecisionTreeModel.hpp"

DecisionTreeModel::DecisionTreeModel()
{
	root_ = nullptr;
}

void DecisionTreeModel::init(
		const std::string & ability, const std::string & left_entity, const std::string & right_entity)
{
	root_ = std::make_shared<DecisionNode>();
	root_->ability = ability;

	auto left_node = std::make_shared<DecisionNode>();
	left_node->entity = left_entity;
	add_left(root_, left_node);

	auto right_node = std::make_shared<DecisionNode>();
	right_node->entity = right_entity;
	add_right(root_, right_node);
}

void DecisionTreeModel::add_left(std::shared_ptr<DecisionNode> current, std::shared_ptr<DecisionNode> child)
{
	child->parent = current;
	current->left = child;
	child->side = DecisionNode::DecisionNodeSide::LEFT;
	nodes_.emplace_back(child);
}

void DecisionTreeModel::add_right(std::shared_ptr<DecisionNode> current, std::shared_ptr<DecisionNode> child)
{
	child->parent = current;
	current->right = child;
	child->side = DecisionNode::DecisionNodeSide::RIGHT;
	nodes_.emplace_back(child);
}

void DecisionTreeModel::add(
		std::shared_ptr<DecisionNode> current, const std::string & entity, const std::string & ability)
{
	if (!current)
	{
		return;
	}

	auto entity_node = std::make_shared<DecisionNode>();
	entity_node->entity = entity;

	auto ability_node = std::make_shared<DecisionNode>();
	ability_node->ability = ability;

	if (current->side == DecisionNode::DecisionNodeSide::LEFT)
	{
		add_left(current->parent, ability_node);
	}
	else
	{
		add_right(current->parent, ability_node);
	}
	add_right(ability_node, entity_node);

	ability_node->left = current;
	current->parent = ability_node;
	current->side = DecisionNode::DecisionNodeSide::LEFT;
}

std::shared_ptr<DecisionNode> DecisionTreeModel::root()
{
	return root_;
}
