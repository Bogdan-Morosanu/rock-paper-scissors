#ifndef APP_MOVE_COMMAND_PARSERS
#define APP_MOVE_COMMAND_PARSERS

#include <iostream>

#include "parser/Commands.hpp"
#include "app/Game.hpp"

namespace app
{
    class RockCommand {
    public:

	explicit
	RockCommand(Game &game)
	    : mGame(&game)
	{ }

	std::string name() const
	{
	    return "rock";
	}

	void issue() const
	{
	    std::cout << "rock!" << std::endl;
	    mGame->registerPlayerMove(rps::Move::ROCK);
	}

    private:

	// a pointer becase we need this class to support copy/move/swap
	app::Game *mGame;
    };

    class PaperCommand {
    public:

	explicit
	PaperCommand(Game &game)
	    : mGame(&game)
	{ }
	
	std::string name() const
	{
	    return "paper";
	}

	void issue() const
	{
	    std::cout << "paper!" << std::endl;
	    mGame->registerPlayerMove(rps::Move::PAPER);
	}

    private:

	// a pointer becase we need this class to support copy/move/swap
	app::Game *mGame;
    };

    class ScissorsCommand {
    public:

	explicit
	ScissorsCommand(Game &game)
	    : mGame(&game)
	{ }
	
	std::string name() const
	{
	    return "scissors";
	}

	void issue() const
	{
	    std::cout << "scissors!" << std::endl;
	    mGame->registerPlayerMove(rps::Move::SCISSORS);
	}

    private:

	// a pointer becase we need this class to support copy/move/swap
	app::Game *mGame;
    };
}

#endif
