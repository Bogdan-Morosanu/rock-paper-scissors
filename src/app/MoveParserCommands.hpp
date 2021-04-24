#ifndef APP_MOVE_PARSER_COMMANDS
#define APP_MOVE_PARSER_COMMANDS

#include "parser/Commands.hpp"

namespace app
{
    class RockCommand {
    public:

	const std::string& name() const
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

	const std::string& name() const
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

	const std::string& name() const
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
