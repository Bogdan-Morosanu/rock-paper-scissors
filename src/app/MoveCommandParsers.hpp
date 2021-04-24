#ifndef APP_MOVE_COMMAND_PARSERS
#define APP_MOVE_COMMAND_PARSERS

#include <iostream>

#include "parser/Commands.hpp"

namespace app
{
    class RockCommand {
    public:

	std::string name() const
	{
	    return "rock";
	}

	void issue() const
	{
	    std::cout << "rock!" << std::endl;
	}
    };

    class PaperCommand {
    public:

	std::string name() const
	{
	    return "paper";
	}

	void issue() const
	{
	    std::cout << "paper!" << std::endl;
	}
    };

    class ScissorsCommand {
    public:

	std::string name() const
	{
	    return "scissors";
	}

	void issue() const
	{
	    std::cout << "scissors!" << std::endl;
	}
    };
}

#endif
