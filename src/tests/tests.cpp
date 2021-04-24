#include "game/Move.hpp"
#include "game/GameHistory.hpp"

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

void runGameHistoryTests();

int main(int argc, char **argv)
{
    runMoveTests();

    runGameHistoryTests();

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

    message("Move logic tests success!\n");
}


void runGameHistoryTests()
{
    message("Running game history tests...");

    {
	message("\tValid empty history");
	
	rps::GameHistory history(0u, 1u);

	auto result = history.result();
	require(result.left.score == 0u && result.right.score == 0u, "failure case: initial score not 0 - 0");
	require(result.left.player == 0u && result.right.player == 1u, "failuer case: player ids not propagated to history");
    }

    {
	message("\tSingle round win");
	
	rps::GameHistory history(0u, 1u);

	history.add(rps::Move::ROCK, rps::Move::SCISSORS);
	
	auto result = history.result();
	
	require(result.left.score == 1u && result.right.score == 0u, "failure case: one round, should result in 1 - 0 score");
    }


    {
	message("\tSingle round draw");
	
	rps::GameHistory history(0u, 1u);

	history.add(rps::Move::ROCK, rps::Move::ROCK);
	
	auto result = history.result();
	
	require(result.left.score == 0u && result.right.score == 0u, "failure case: one round, should result in 0 - 0 score");
    }

    {
	message("\tMultiple rounds");
	
	rps::GameHistory history(0u, 1u);

	history.add(rps::Move::PAPER, rps::Move::PAPER);
	history.add(rps::Move::SCISSORS, rps::Move::ROCK);
	history.add(rps::Move::ROCK, rps::Move::PAPER);
	history.add(rps::Move::ROCK, rps::Move::SCISSORS);
	
	auto result = history.result();
	
	require(result.left.score == 1u && result.right.score == 2u, "failure case: three rounds, should result in 1 - 2 score");
    }

    message("Game history tests success!\n");
}
