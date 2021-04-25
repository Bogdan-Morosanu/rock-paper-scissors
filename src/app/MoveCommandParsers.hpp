#ifndef APP_MOVE_COMMAND_PARSERS
#define APP_MOVE_COMMAND_PARSERS

#include <iostream>

#include "parser/Commands.hpp"
#include "app/GameApp.hpp"
#include "app/prompt.hpp"

namespace app
{
    class RockCommand {
    public:

	explicit
	RockCommand(GameApp &game)
	    : mGame(&game)
	{ }

	std::string name() const
	{
	    return "rock";
	}

	void issue() const
	{
	    mGame->registerPlayerMove(rps::Move::ROCK);

	    if (mGame->roundsLeft() != 0u) {
		displayPrompt();
	    }
	}

    private:

	// a pointer becase we need this class to support copy/move/swap
	app::GameApp *mGame;
    };

    class PaperCommand {
    public:

	explicit
	PaperCommand(GameApp &game)
	    : mGame(&game)
	{ }
	
	std::string name() const
	{
	    return "paper";
	}

	void issue() const
	{
	    mGame->registerPlayerMove(rps::Move::PAPER);

	    if (mGame->roundsLeft() != 0u) {
		displayPrompt();
	    }
	}

    private:

	// a pointer becase we need this class to support copy/move/swap
	app::GameApp *mGame;
    };

    class ScissorsCommand {
    public:

	explicit
	ScissorsCommand(GameApp &game)
	    : mGame(&game)
	{ }
	
	std::string name() const
	{
	    return "scissors";
	}

	void issue() const
	{
	    mGame->registerPlayerMove(rps::Move::SCISSORS);

	    if (mGame->roundsLeft() != 0u) {
		displayPrompt();
	    }
	}

    private:

	// a pointer becase we need this class to support copy/move/swap
	app::GameApp *mGame;
    };
}

#endif
