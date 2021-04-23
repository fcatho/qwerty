#include "DecisionTreeModel.hpp"

std::shared_ptr<ModelDataInterface> DecisionNode::right() const
{
	return right_;
}

std::shared_ptr<ModelDataInterface> DecisionNode::left()  const
{
	return left_;
}

std::shared_ptr<ModelDataInterface> DecisionNode::parent() const
{
	return parent_;
}

std::string & DecisionNode::property()
{
	return property_;
}

std::string & DecisionNode::entity()
{
	return entity_;
}

void DecisionNode::right(std::shared_ptr<ModelDataInterface> right)
{
	right_ = right;
}

void DecisionNode::left(std::shared_ptr<ModelDataInterface> left)
{
	left_ = left;
}

void DecisionNode::parent(std::shared_ptr<ModelDataInterface> parent)
{
	parent_ = parent;
}

void DecisionNode::property(const std::string & property)
{
	property_ = property;
}

void DecisionNode::entity(const std::string & entity)
{
	entity_ = entity;
}

DecisionTreeModel::DecisionTreeModel()
{
	root_ = nullptr;
}

void DecisionTreeModel::init(
		const std::string & property, const std::string & left_entity, const std::string & right_entity)
{
	root_ = std::make_shared<DecisionNode>();
	root_->property(property);

	auto left_node = std::make_shared<DecisionNode>();
	left_node->entity(left_entity);
	add_left(root_, left_node);

	auto right_node = std::make_shared<DecisionNode>();
	right_node->entity(right_entity);
	add_right(root_, right_node);
}

void DecisionTreeModel::add_left(std::shared_ptr<ModelDataInterface> current, std::shared_ptr<ModelDataInterface> child)
{
	child->parent(current);
	current->left(child);
	nodes_.push_back(child);
}

void DecisionTreeModel::add_right(std::shared_ptr<ModelDataInterface> current, std::shared_ptr<ModelDataInterface> child)
{
	child->parent(current);
	current->right(child);
	nodes_.push_back(child);
}

void DecisionTreeModel::add_left_to(
		std::shared_ptr<ModelDataInterface> current, const std::string & entity, const std::string & property)
{
	if (!current)
	{
		return;
	}

	auto entity_node = std::make_shared<DecisionNode>();
	entity_node->entity(entity);

	auto property_node = std::make_shared<DecisionNode>();
	property_node->property(property);

	add_left(current->parent(), property_node);
	add_right(property_node, entity_node);

	property_node->left(current);
	current->parent(property_node);
}

void DecisionTreeModel::add_right_to(
		std::shared_ptr<ModelDataInterface> current, const std::string & entity, const std::string & property)
{
	if (!current)
	{
		return;
	}

	auto entity_node = std::make_shared<DecisionNode>();
	entity_node->entity(entity);

	auto property_node = std::make_shared<DecisionNode>();
	property_node->property(property);

	add_right(current->parent(), property_node);
	add_right(property_node, entity_node);

	property_node->left(current);
	current->parent(property_node);
}


std::shared_ptr<ModelDataInterface> DecisionTreeModel::root()
{
	return root_;
}

