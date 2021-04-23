#ifndef MODEL_INTERFACE
#define MODEL_INTERFACE

#include <memory>
#include <vector>

class ModelDataInterface
{
public:
	virtual std::shared_ptr<ModelDataInterface> right() const = 0;
	virtual std::shared_ptr<ModelDataInterface> left()  const = 0;
	virtual std::shared_ptr<ModelDataInterface> parent() const = 0;
	virtual std::string & property() = 0;
	virtual std::string & entity() = 0;

	virtual void right(std::shared_ptr<ModelDataInterface> right) = 0;
	virtual void left(std::shared_ptr<ModelDataInterface> left) = 0;
	virtual void parent(std::shared_ptr<ModelDataInterface> parent) = 0;
	virtual void property(const std::string & property) = 0;
	virtual void entity(const std::string & entity) = 0;
};


class ModelInterface
{
public:
	virtual ~ModelInterface() {}
	virtual void init(const std::string & property, const std::string & left_entity, const std::string & right_entity) = 0;
	virtual void add_right_to(std::shared_ptr<ModelDataInterface> current, const std::string & entity, const std::string & property) = 0;
	virtual void add_left_to(std::shared_ptr<ModelDataInterface> current, const std::string & entity, const std::string & property) = 0;
	virtual std::shared_ptr<ModelDataInterface> root() = 0;

protected:
	std::shared_ptr<ModelDataInterface> root_;

};

#endif //MODEL_INTERFACE

