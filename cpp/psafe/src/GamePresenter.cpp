#include "GamePresenter.hpp"

GamePresenter::GamePresenter(std::shared_ptr<ModelInterface> model, std::shared_ptr<ViewInterface> view)
{
	model_ = model;
	view_ = view;
	model_->init("live in water", "monkey", "shark");
}

void GamePresenter::run()
{
	if (!view_->keep_going())
	{
		return;
	}

	auto node = model_->root();
	while (1)
	{
		if (node->entity.size())
		{
			if (view_->try_answer(node->entity))
			{
				view_->win();
			}
			else
			{
				auto new_entity = view_->ask_entity();
				auto new_ability = view_->ask_ability(node->entity, new_entity);
				model_->add(node, new_entity, new_ability);
			}

			if (view_->keep_going())
			{
				node = model_->root();
				continue;
			}
			break;
		}

		if (view_->check_ability(node->ability))
		{
			node = node->right;
		}
		else
		{
			node = node->left;
		}
	}
}

