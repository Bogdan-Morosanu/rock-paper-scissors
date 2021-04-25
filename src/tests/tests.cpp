#include "game/Move.hpp"
#include "game/GameHistory.hpp"
#include "app/GameApp.hpp"

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

void runGameAppTests();

void runOptionTests();

int main(int argc, char **argv)
{
    runMoveTests();

    runGameHistoryTests();

    runGameAppTests();

    return 0;
}

void runGameAppTests()
{
    message("Running game app tests...");

    {
	message("\tNo Ai on construction.");
	app::GameApp game(app::GameApp::LOG_NOTHING);

	require(!game.hasAi(), "failure case: ai populated before user input");
    }

    {
	message("\tAi set after user input");
	app::GameApp game(app::GameApp::LOG_NOTHING);

	game.setAi(ai::Strategy::CYBER_CHICKEN);
	require(game.hasAi(), "failure case: not set after user input");
    }

    {
	message("\tMoves correctly set after user input");
	app::GameApp game(app::GameApp::LOG_NOTHING);

	game.setAi(ai::Strategy::CYBER_CHICKEN);
	game.setNrRounds(10u);
	require(game.roundsLeft() == 10u, "failure case: number of rounds left not set correctly");
    }

    {
	message("\tMoves correctly decremented after round played");
	app::GameApp game(app::GameApp::LOG_NOTHING);

	game.setAi(ai::Strategy::CYBER_CHICKEN);
	game.setNrRounds(10u);

	game.registerPlayerMove(rps::Move::ROCK);
	require(game.roundsLeft() == 9u, "failure case: number of rounds left not decremented after round takes place");

	game.registerPlayerMove(rps::Move::ROCK);
	require(game.roundsLeft() == 8u, "failure case: number of rounds left not decremented after round takes place");
	
	game.registerPlayerMove(rps::Move::ROCK);
	require(game.roundsLeft() == 7u, "failure case: number of rounds left not decremented after round takes place");
    }

    {
	message("\tThrows on playing round in finished game");
	app::GameApp game(app::GameApp::LOG_NOTHING);

	game.setAi(ai::Strategy::CYBER_CHICKEN);
	game.setNrRounds(1u);

	game.registerPlayerMove(rps::Move::ROCK);

	bool hasThrown = false;
	try {
	    game.registerPlayerMove(rps::Move::ROCK);
	} catch(...) {
	    hasThrown = true;
	}

	require(hasThrown, "failure case: no throw when trying to play moves in an already finished game!");
    }

    {
	message("\tThrows on playing round in game without a selected AI");
	app::GameApp game(app::GameApp::LOG_NOTHING);

	game.setNrRounds(1u);
	
	bool hasThrown = false;
	try {
	    game.registerPlayerMove(rps::Move::ROCK);
	} catch(...) {
	    hasThrown = true;
	}

	require(hasThrown, "failure case: no throw when trying to play moves in a game without a selected Ai oponent!");
    }

    message("Game app tests success!\n");
}

void runMoveTests()
{
    message("Running move logic tests...");

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
