#ifndef GAME_TEST
#define GAME_TEST

#include "ViewInterface.hpp"
#include "GamePresenter.hpp"
#include "DecisionTreeModel.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class ViewMock : public ViewInterface
{
public:
	MOCK_METHOD(bool,  keep_going, (), (override));
	MOCK_METHOD(bool,  try_answer, (const std::string &), (override));
	MOCK_METHOD(void,  win, (), (override));
	MOCK_METHOD(bool,  check_property, (const std::string &), (override));
	MOCK_METHOD(std::string, ask_entity, (), (override));
	MOCK_METHOD(std::string, ask_property, (const std::string &, const std::string &), (override));
};


class GameTest : public ::testing::Test
{
protected:
	GameTest()
		: decision_tree_(std::make_shared<DecisionTreeModel>())
		, console_mock_(std::make_shared<ViewMock>())
		, game_(std::make_shared<GamePresenter>(decision_tree_, console_mock_))
	{
	}

	void SetUp()
	{
		auto node = decision_tree_->root();
		decision_tree_->add_right_to(node->right(), "octopus", "eight legs");
		decision_tree_->add_left_to(node->right()->left(), "shrimp", "eat algae");
		decision_tree_->add_left_to(node->left(), "dog", "run");
		decision_tree_->add_right_to(node->left()->right(), "tiger", "hunt");
	}

	std::shared_ptr<DecisionTreeModel> decision_tree_;
	std::shared_ptr<ViewMock> console_mock_;
	std::shared_ptr<GamePresenter> game_;
};

namespace
{

TEST_F(GameTest, finish_just_after_start)
{
	EXPECT_CALL(*console_mock_, keep_going())
		.WillOnce(::testing::Return(false));
	game_->run();
}


TEST_F(GameTest, right_right_leaf_correct)
{
	EXPECT_CALL(*console_mock_, keep_going())
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("live in water"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, check_property("eight legs"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, try_answer("octopus"))
		.WillOnce(::testing::Return(true));

	EXPECT_CALL(*console_mock_, win());

	game_->run();
}

TEST_F(GameTest, right_left_left_leaf_correct)
{
	EXPECT_CALL(*console_mock_, keep_going())
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("live in water"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, check_property("eight legs"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("eat algae"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, try_answer("shark"))
		.WillOnce(::testing::Return(true));

	EXPECT_CALL(*console_mock_, win());

	game_->run();
}

TEST_F(GameTest, right_left_right_leaf_correct)
{
	EXPECT_CALL(*console_mock_, keep_going())
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("live in water"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, check_property("eight legs"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("eat algae"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, try_answer("shrimp"))
		.WillOnce(::testing::Return(true));

	EXPECT_CALL(*console_mock_, win());

	game_->run();
}

TEST_F(GameTest, left_left_leaf_correct)
{
	EXPECT_CALL(*console_mock_, keep_going())
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("live in water"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("run"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, try_answer("monkey"))
		.WillOnce(::testing::Return(true));

	EXPECT_CALL(*console_mock_, win());

	game_->run();
}

TEST_F(GameTest, left_right_right_leaf_correct)
{
	EXPECT_CALL(*console_mock_, keep_going())
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("live in water"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("run"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, check_property("hunt"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, try_answer("tiger"))
		.WillOnce(::testing::Return(true));

	EXPECT_CALL(*console_mock_, win());

	game_->run();
}

TEST_F(GameTest, left_right_left_leaf_correct)
{
	EXPECT_CALL(*console_mock_, keep_going())
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("live in water"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("run"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, check_property("hunt"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, try_answer("dog"))
		.WillOnce(::testing::Return(true));

	EXPECT_CALL(*console_mock_, win());

	game_->run();
}

TEST_F(GameTest, left_right_right_leaf_is_wrong)
{
	EXPECT_CALL(*console_mock_, keep_going())
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("live in water"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("run"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, check_property("hunt"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, try_answer("tiger"))
		.WillOnce(::testing::Return(false));

	EXPECT_CALL(*console_mock_, ask_entity());
	EXPECT_CALL(*console_mock_, ask_property(::testing::_, ::testing::_));

	game_->run();
}

TEST_F(GameTest, left_right_left_leaf_is_wrong)
{
	EXPECT_CALL(*console_mock_, keep_going())
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("live in water"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("run"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, check_property("hunt"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, try_answer("dog"))
		.WillOnce(::testing::Return(false));

	EXPECT_CALL(*console_mock_, ask_entity());
	EXPECT_CALL(*console_mock_, ask_property(::testing::_, ::testing::_));

	game_->run();
}

TEST_F(GameTest, win_continue_finish)
{
	EXPECT_CALL(*console_mock_, keep_going())
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("live in water"))
		.WillOnce(::testing::Return(true))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, check_property("eight legs"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, try_answer("octopus"))
		.WillOnce(::testing::Return(true));
	EXPECT_CALL(*console_mock_, check_property("run"))
		.WillOnce(::testing::Return(false));
	EXPECT_CALL(*console_mock_, try_answer("monkey"))
		.WillOnce(::testing::Return(true));

	EXPECT_CALL(*console_mock_, win()).Times(2);

	game_->run();
}

}

#endif //GAME_TEST
