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

    rps::PlayerId p1{1};
    rps::PlayerId p2{2};

    {
	message("\tRock vs Rock");
	auto result = rps::result(rps::Move{p1, rps::Move::ROCK}, rps::Move{p2, rps::Move::ROCK});
	require(result.type == rps::RoundResult::DRAW, "failure case: ROCK draw vs ROCK");
    }
    {
	message("\tRock vs Paper");
	auto result = rps::result(rps::Move{p1, rps::Move::ROCK}, rps::Move{p2, rps::Move::PAPER});
	require(result.type == rps::RoundResult::WIN && result.winner == p2,
		"failure case: ROCK loss vs PAPER");
    }
    {
	message("\tRock vs Scissor");
	auto result = rps::result(rps::Move{p1, rps::Move::ROCK}, rps::Move{p2, rps::Move::SCISSORS});
	require(result.type == rps::RoundResult::WIN && result.winner == p1,
		"failure case: ROCK win vs SCISSORS");
    }
    {
	message("\tPaper vs Rock");
	auto result = rps::result(rps::Move{p1, rps::Move::PAPER}, rps::Move{p2, rps::Move::ROCK});
	require(result.type == rps::RoundResult::WIN && result.winner == p1,
		"failure case: PAPER win vs ROCK");
    }
    {
	message("\tPaper vs Paper");
	auto result = rps::result(rps::Move{p1, rps::Move::PAPER}, rps::Move{p2, rps::Move::PAPER});
	require(result.type == rps::RoundResult::DRAW, "failure case: PAPER draw vs PAPER");
    }
    {
	message("\tPaper vs Scissors");
	auto result = rps::result(rps::Move{p1, rps::Move::PAPER}, rps::Move{p2, rps::Move::SCISSORS});
	require(result.type == rps::RoundResult::WIN && result.winner == p2,
		"failure case: PAPER loss vs SCISSORS");
    }
    {
	message("\tScissors vs Rock");
	auto result = rps::result(rps::Move{p1, rps::Move::SCISSORS}, rps::Move{p2, rps::Move::ROCK});
	require(result.type == rps::RoundResult::WIN && result.winner == p2,
		"failure case: SCISSORS loss vs ROCK");
    }
    {
	message("\tScissors vs Paper");
	auto result = rps::result(rps::Move{p1, rps::Move::SCISSORS}, rps::Move{p2, rps::Move::PAPER});
	require(result.type == rps::RoundResult::WIN && result.winner == p1,
		"failure case: SCISSORS win vs PAPER");
    }
    {
	message("\tScissors vs Scissors");
	auto result = rps::result(rps::Move{p1, rps::Move::SCISSORS}, rps::Move{p2, rps::Move::SCISSORS});
	require(result.type == rps::RoundResult::DRAW, "failure case: SCISSORS draw vs SCISSORS");
    }

    message("Move logic tests success!");
}
