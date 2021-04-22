#ifndef GAME_PRESENTER
#define GAME_PRESENTER

#include "PresenterInterface.hpp"

class GamePresenter : public PresenterInterface
{
public:
	GamePresenter(std::shared_ptr<ModelInterface> model, std::shared_ptr<ViewInterface> view);
	void run() override;
};

#endif //GAME_PRESENTER
