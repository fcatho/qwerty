#include "RPSTest.hpp"
#include "ConsoleReader.hpp"
#include "ConsoleWriter.hpp"
#include "ComputerPlayer.hpp"

void RPSTest::SetUp()
{
	writer_ = std::make_shared<WriterStub>();
	reader_ = std::make_shared<ReaderStub>();
	playerA_ = std::make_shared<HumanPlayer>("michael", reader_, writer_);
	playerB_ = std::make_shared<HumanPlayer>("spock", reader_, writer_);
	rps_ = std::make_shared<RPSApp>(playerA_, playerB_, writer_);
}

void RPSTest::expect_end()
{
	play(playerA_, 'X');
}

void RPSTest::play(std::shared_ptr<HumanPlayer> player, const char symbol)
{
	EXPECT_CALL(*writer_, write("Choose P, R or S: "));
	EXPECT_CALL(*reader_, read()).WillOnce(::testing::Return(std::string(&symbol, 1)));
}

void RPSTest::expect_draw()
{
	::testing::InSequence seq;
	EXPECT_CALL(*writer_, write(::testing::_));
	EXPECT_CALL(*writer_, write("draw\n\n"));
}

void RPSTest::expect_winner(std::shared_ptr<HumanPlayer> player)
{
	::testing::InSequence seq;
	EXPECT_CALL(*writer_, write(::testing::_));
	EXPECT_CALL(*writer_, write(player->id() + " win\n\n"));
}


TEST_F(RPSTest, dont_ask_B_if_A_symbol_invalid)
{
	::testing::InSequence seq;
	play(playerA_, 'X');
	EXPECT_CALL(*writer_, write(::testing::_)).Times(0);
	rps_->run();
}

TEST_F(RPSTest, dont_show_symbols_if_B_invalid)
{
	::testing::InSequence seq;
	play(playerA_, 'P');
	play(playerB_, 'X');
	EXPECT_CALL(*writer_, write(::testing::_)).Times(0);
	rps_->run();
}

TEST_F(RPSTest, display_symbols)
{
	::testing::InSequence seq;
	play(playerA_, 'P');
	play(playerB_, 'S');
	EXPECT_CALL(*writer_, write("P vs S\n"));
	EXPECT_CALL(*writer_, write(::testing::_));
	expect_end();

	rps_->run();
}

TEST_F(RPSTest, paper_vs_paper_is_draw)
{
	::testing::InSequence seq;
	play(playerA_, 'P');
	play(playerB_, 'P');
	expect_draw();
	expect_end();

	rps_->run();
}

TEST_F(RPSTest, paper_vs_rock_A_wins)
{
	::testing::InSequence seq;
	play(playerA_, 'P');
	play(playerB_, 'R');
	expect_winner(playerA_);
	expect_end();

	rps_->run();
}

TEST_F(RPSTest, paper_vs_scissors_B_wins)
{
	::testing::InSequence seq;
	play(playerA_, 'P');
	play(playerB_, 'S');
	expect_winner(playerB_);
	expect_end();

	rps_->run();
}

TEST_F(RPSTest, rock_vs_paper_B_wins)
{
	::testing::InSequence seq;
	play(playerA_, 'R');
	play(playerB_, 'P');
	expect_winner(playerB_);
	expect_end();

	rps_->run();
}

TEST_F(RPSTest, rock_vs_rock_is_draw)
{
	::testing::InSequence seq;
	play(playerA_, 'R');
	play(playerB_, 'R');
	expect_draw();
	expect_end();

	rps_->run();
}

TEST_F(RPSTest, rock_vs_scissors_A_wins)
{
	::testing::InSequence seq;
	play(playerA_, 'R');
	play(playerB_, 'S');
	expect_winner(playerA_);
	expect_end();

	rps_->run();
}

TEST_F(RPSTest, scissors_vs_paper_A_wins)
{
	::testing::InSequence seq;
	play(playerA_, 'S');
	play(playerB_, 'P');
	expect_winner(playerA_);
	expect_end();

	rps_->run();
}

TEST_F(RPSTest, scissors_vs_rock_B_wins)
{
	::testing::InSequence seq;
	play(playerA_, 'S');
	play(playerB_, 'R');
	expect_winner(playerB_);
	expect_end();

	rps_->run();
}

TEST_F(RPSTest, scissors_vs_scissors_is_draw)
{
	::testing::InSequence seq;
	play(playerA_, 'S');
	play(playerB_, 'S');
	expect_draw();
	expect_end();

	rps_->run();
}

TEST_F(RPSTest, write_standard_output)
{
	ConsoleWriter writer;
	std::ostringstream oss;
	std::streambuf * cout_streambuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());
	writer.write("rps_game");
	std::cout.rdbuf(cout_streambuf);

	ASSERT_STREQ("rps_game", oss.str().c_str());
}

TEST_F(RPSTest, read_standard_input)
{
	ConsoleReader reader;
	std::istringstream iss("rps_game");
	std::streambuf* cin_streambuf = std::cin.rdbuf();
	std::cin.rdbuf(iss.rdbuf());
	std::string ans = reader.read();
	std::cout.rdbuf(cin_streambuf);

	ASSERT_STREQ("rps_game", ans.c_str());
}

TEST_F(RPSTest, computer_play)
{
	ComputerPlayer spock("spock");
	static const std::set<char> options{'R', 'P', 'S'};
	ASSERT_TRUE(options.find(spock.play()) != options.end());
}

