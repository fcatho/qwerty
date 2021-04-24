#ifndef GAME_TEST
#define GAME_TEST

#include "ViewInterface.hpp"
#include "ConsoleView.hpp"
#include "GamePresenter.hpp"
#include "DecisionTreeModel.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class ViewMock : public ViewInterface
{
public:
	MOCK_METHOD(bool, keep_going, (), (override));
	MOCK_METHOD(bool, try_answer, (const std::string &), (override));
	MOCK_METHOD(void, win, (), (override));
	MOCK_METHOD(bool, check_property, (const std::string &), (override));
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

class ConsoleIOMock : public ConsoleIO
{
public:
	MOCK_METHOD(void, write, (const std::string &), (override));
	MOCK_METHOD(std::string, read, (), (override));
};

class ConsoleViewStub : public ConsoleView
{
public:
	ConsoleViewStub()
		:io_mock_(new ConsoleIOMock())
	{
		io_.reset(static_cast<ConsoleIO*>(io_mock_));
	}
	ConsoleIOMock * io_mock_;
};

class ConsoleViewTest : public ::testing::Test
{
protected:
	ConsoleViewStub console_;
};

class ConsoleIOTest : public ::testing::Test
{
protected:
	ConsoleIO io_;
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

TEST_F(ConsoleViewTest, continue_lower_case)
{
	EXPECT_CALL(*console_.io_mock_, write(::testing::_)).Times(3);
	EXPECT_CALL(*console_.io_mock_, read()).WillOnce(::testing::Return("c"));

	ASSERT_TRUE(console_.keep_going());
}

TEST_F(ConsoleViewTest, continue_upper_case)
{
	EXPECT_CALL(*console_.io_mock_, write(::testing::_)).Times(3);
	EXPECT_CALL(*console_.io_mock_, read()).WillOnce(::testing::Return("C"));

	ASSERT_TRUE(console_.keep_going());
}

TEST_F(ConsoleViewTest, cancel_lower_case)
{
	EXPECT_CALL(*console_.io_mock_, write(::testing::_)).Times(3);
	EXPECT_CALL(*console_.io_mock_, read()).WillOnce(::testing::Return("X"));

	EXPECT_CALL(*console_.io_mock_, write("See you later!\n"));
	ASSERT_FALSE(console_.keep_going());
}

TEST_F(ConsoleViewTest, cancel_upper_case)
{
	EXPECT_CALL(*console_.io_mock_, write(::testing::_)).Times(3);
	EXPECT_CALL(*console_.io_mock_, read()).WillOnce(::testing::Return("x"));

	EXPECT_CALL(*console_.io_mock_, write("See you later!\n"));
	ASSERT_FALSE(console_.keep_going());
}

TEST_F(ConsoleViewTest, invalid_answer_keep_going)
{
	EXPECT_CALL(*console_.io_mock_, write("\n\n\nGuessing game!!!\n\n\n")).Times(2);
	EXPECT_CALL(*console_.io_mock_, write("Think about an animal...\n\n")).Times(2);
	EXPECT_CALL(*console_.io_mock_, write("C - Continue\nX - Exit\n")).Times(2);
	EXPECT_CALL(*console_.io_mock_, write("\nSorry, invalid option... Try again, please\n"));
	EXPECT_CALL(*console_.io_mock_, write("See you later!\n"));
	EXPECT_CALL(*console_.io_mock_, read())
		.WillOnce(::testing::Return("0"))
		.WillOnce(::testing::Return("x"));

	ASSERT_FALSE(console_.keep_going());
}

TEST_F(ConsoleViewTest, try_answer_returns_yes)
{
	std::string entity = "dog";
	EXPECT_CALL(*console_.io_mock_,
			write("Is the animal you thought a " + entity + "? (Y/N) ")).Times(1);
	EXPECT_CALL(*console_.io_mock_, read())
		.WillOnce(::testing::Return("Y"));
	ASSERT_TRUE(console_.try_answer(entity));
}

TEST_F(ConsoleViewTest, try_answer_returns_no)
{
	std::string entity = "dog";
	EXPECT_CALL(*console_.io_mock_,
			write("Is the animal you thought a " + entity + "? (Y/N) ")).Times(1);
	EXPECT_CALL(*console_.io_mock_, read())
		.WillOnce(::testing::Return("N"));
	ASSERT_FALSE(console_.try_answer(entity));
}

TEST_F(ConsoleViewTest, check_property_returns_yes)
{
	std::string property = "fly";
	EXPECT_CALL(*console_.io_mock_,
			write("Does the animal you thought " + property + "? (Y/N) ")).Times(1);
	EXPECT_CALL(*console_.io_mock_, read())
		.WillOnce(::testing::Return("y"));
	ASSERT_TRUE(console_.check_property(property));
}

TEST_F(ConsoleViewTest, check_property_returns_no)
{
	std::string property = "fly";
	EXPECT_CALL(*console_.io_mock_,
			write("Does the animal you thought " + property + "? (Y/N) ")).Times(1);
	EXPECT_CALL(*console_.io_mock_, read())
		.WillOnce(::testing::Return("n"));
	ASSERT_FALSE(console_.check_property(property));
}

TEST_F(ConsoleViewTest, invalid_choice_yes_no_question)
{
	std::string property = "fly";
	EXPECT_CALL(*console_.io_mock_,
			write("Does the animal you thought " + property + "? (Y/N) ")).Times(2);
	EXPECT_CALL(*console_.io_mock_, write("\nInvalid choice\n"));
	EXPECT_CALL(*console_.io_mock_, read())
		.WillOnce(::testing::Return("0"))
		.WillOnce(::testing::Return("n"));
	ASSERT_FALSE(console_.check_property(property));
}


TEST_F(ConsoleViewTest, ask_entity)
{
	std::string new_entity = "dog";
	EXPECT_CALL(*console_.io_mock_,
			write("What was the animal you thought about? ")).Times(1);
	EXPECT_CALL(*console_.io_mock_, read()).WillOnce(::testing::Return("dog"));

	ASSERT_STREQ("dog", console_.ask_entity().c_str());
}

TEST_F(ConsoleViewTest, ask_property)
{
	std::string new_entity = "dog";
	std::string current_entity = "shark";
	EXPECT_CALL(*console_.io_mock_,
			write("What does a " + new_entity + " do, that a " + current_entity + " does not? "));
	EXPECT_CALL(*console_.io_mock_, read()).WillOnce(::testing::Return("bark"));

	ASSERT_STREQ("bark", console_.ask_property(current_entity, new_entity).c_str());
}

TEST_F(ConsoleViewTest, win_message)
{
	EXPECT_CALL(*console_.io_mock_, write("I win!!!\n")).Times(1);
	console_.win();
}

TEST_F(ConsoleIOTest, write_data)
{
	std::ostringstream oss;
	std::streambuf* p_cout_streambuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());
	io_.write("guess_game");
	std::cout.rdbuf(p_cout_streambuf);

	ASSERT_STREQ("guess_game", oss.str().c_str());
}

TEST_F(ConsoleIOTest, read_data)
{
	std::istringstream iss("guess_game");
	std::streambuf* p_cin_streambuf = std::cin.rdbuf();
	std::cin.rdbuf(iss.rdbuf());
	std::string ans = io_.read();
	std::cout.rdbuf(p_cin_streambuf);

	ASSERT_STREQ("guess_game", ans.c_str());
}




}

#endif //GAME_TEST
