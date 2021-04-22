#ifndef PRESENTER_INTERFACE
#define PRESENTER_INTERFACE

#include "ModelInterface.hpp"
#include "ViewInterface.hpp"

class PresenterInterface
{
public:
	virtual ~PresenterInterface() {};
	virtual void run() = 0;

protected:
	std::shared_ptr<ModelInterface> model_;
	std::shared_ptr<ViewInterface> view_;
};

#endif //PRESENTER_INTERFACE

