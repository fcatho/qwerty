#ifndef DECISION_TREE_MODEL
#define DECISION_TREE_MODEL

#include "ModelInterface.hpp"

class DecisionNode : public ModelDataInterface
{
public:
	std::shared_ptr<ModelDataInterface> right() const override;
	std::shared_ptr<ModelDataInterface> left()  const override;
	std::shared_ptr<ModelDataInterface> parent() const override;
	std::string & property() override;
	std::string & entity() override;

	void right(std::shared_ptr<ModelDataInterface> right) override;
	void left(std::shared_ptr<ModelDataInterface> left) override;
	void parent(std::shared_ptr<ModelDataInterface> parent) override;
	void property(const std::string & property) override;
	void entity(const std::string & entity) override;

private:
	std::shared_ptr<ModelDataInterface> right_;
	std::shared_ptr<ModelDataInterface> left_;
	std::shared_ptr<ModelDataInterface> parent_;
	std::string property_;
	std::string entity_;
};

class DecisionTreeModel : public ModelInterface
{
public:
	DecisionTreeModel();
	void init(
			const std::string & property,
			const std::string & left_entity,
			const std::string & right_entity) override;
	void add_left_to(
			std::shared_ptr<ModelDataInterface> current,
			const std::string & entity,
			const std::string & property) override;
	void add_right_to(
			std::shared_ptr<ModelDataInterface> current,
			const std::string & entity,
			const std::string & property) override;
	std::shared_ptr<ModelDataInterface> root() override;

private:
	void add_left(std::shared_ptr<ModelDataInterface> current, std::shared_ptr<ModelDataInterface> child);
	void add_right(std::shared_ptr<ModelDataInterface> current, std::shared_ptr<ModelDataInterface> child);
	std::vector<std::shared_ptr<ModelDataInterface>> nodes_;

};

#endif // DECISION_TREE_MODEL

