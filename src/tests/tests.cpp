#include "game/Move.hpp"

#include <iostream>

namespace {

    void fail(const std::string &msg)
    {
	std::cerr << msg << std::endl;
	std::exit(EXIT_FAILURE);
    }

    void message(const std::string &msg)
    {
	std::cout << msg << std::endl;
    }				       

    void require(bool shouldBeTrue, const std::string &msg)
    {
	if (!shouldBeTrue) {
	    fail(msg);
	}
    }
}

void runMoveTests();

int main(int argc, char **argv)
{
    runMoveTests();

    return 0;
}

void runMoveTests()
{
    message("Running move logic Tests...");

    {
	message("\tRock vs Rock");
	auto result = rps::roundResult(rps::Move::ROCK, rps::Move::ROCK);
	require(result == rps::RoundResult::DRAW, "failure case: ROCK draw vs ROCK");
    }
    {
	message("\tRock vs Paper");
	auto result = rps::roundResult(rps::Move::ROCK, rps::Move::PAPER);
	require(result == rps::RoundResult::WIN_RIGHT, "failure case: ROCK loss vs PAPER");
    }
    {
	message("\tRock vs Scissor");
	auto result = rps::roundResult(rps::Move::ROCK, rps::Move::SCISSORS);
	require(result == rps::RoundResult::WIN_LEFT, "failure case: ROCK win vs SCISSORS");
    }
    {
	message("\tPaper vs Rock");
	auto result = rps::roundResult(rps::Move::PAPER, rps::Move::ROCK);
	require(result == rps::RoundResult::WIN_LEFT, "failure case: PAPER win vs ROCK");
    }
    {
	message("\tPaper vs Paper");
	auto result = rps::roundResult(rps::Move::PAPER, rps::Move::PAPER);
	require(result == rps::RoundResult::DRAW, "failure case: PAPER draw vs PAPER");
    }
    {
	message("\tPaper vs Scissors");
	auto result = rps::roundResult(rps::Move::PAPER, rps::Move::SCISSORS);
	require(result == rps::RoundResult::WIN_RIGHT, "failure case: PAPER loss vs SCISSORS");
    }
    {
	message("\tScissors vs Rock");
	auto result = rps::roundResult(rps::Move::SCISSORS, rps::Move::ROCK);
	require(result == rps::RoundResult::WIN_RIGHT, "failure case: SCISSORS loss vs ROCK");
    }
    {
	message("\tScissors vs Paper");
	auto result = rps::roundResult(rps::Move::SCISSORS, rps::Move::PAPER);
	require(result == rps::RoundResult::WIN_LEFT, "failure case: SCISSORS win vs PAPER");
    }
    {
	message("\tScissors vs Scissors");
	auto result = rps::roundResult(rps::Move::SCISSORS, rps::Move::SCISSORS);
	require(result == rps::RoundResult::DRAW, "failure case: SCISSORS draw vs SCISSORS");
    }

    message("Move logic tests success!");
}
