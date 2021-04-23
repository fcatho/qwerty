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
	bool was_right = false;
	while (1)
	{
		if (node->entity().size())
		{
			if (view_->try_answer(node->entity()))
			{
				view_->win();
			}
			else
			{
				auto new_entity = view_->ask_entity();
				auto new_property = view_->ask_property(node->entity(), new_entity);
				if (was_right)
				{
					model_->add_right_to(node, new_entity, new_property);
				}
				else
				{
					model_->add_left_to(node, new_entity, new_property);
				}
			}

			if (view_->keep_going())
			{
				node = model_->root();
				continue;
			}
			break;
		}

		if ((was_right = view_->check_property(node->property())))
		{
			node = node->right();
		}
		else
		{
			node = node->left();
		}
	}
}

