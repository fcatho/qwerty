#ifndef RPSTEST_HPP
#define RPSTEST_HPP

#include "RPSApp.hpp"
#include "HumanPlayer.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class WriterStub : public IWriter
{
public:
	MOCK_METHOD(void, write, (const std::string &), (override));
};

class ReaderStub : public IReader
{
public:
	MOCK_METHOD(std::string, read, (), (override));
};


class RPSTest : public ::testing::Test
{
protected:
	void SetUp() override;
	void expect_end();
	void play(std::shared_ptr<HumanPlayer> player, const PlayerOption option);
	void expect_draw();
	void expect_winner(std::shared_ptr<HumanPlayer> player);

	std::shared_ptr<RPSApp> rps_;
	std::shared_ptr<HumanPlayer> playerA_;
	std::shared_ptr<HumanPlayer> playerB_;
	std::shared_ptr<WriterStub> writer_;
	std::shared_ptr<ReaderStub> reader_;
};

#endif // RPSTEST_HPP

