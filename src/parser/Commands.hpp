#ifndef PSR_COMMANDS
#define PSR_COMMANDS

#include <string>
#include <regex>
#include <cstdlib>

namespace psr {

    /// @brief adapts a Unary Command object to be included in a Case parser.
    ///        This parses a command in the form of "<command-name> <mandatory-argument>".
    ///        You need to provide a copy or move-constructible type with the member functions:
    ///              1) std::string name()       - gives the name of the command
    ///
    ///              2) std::string pattern()    - gives the regex pattern of strings you want to
    ///                                            accept as arguments.
    ///
    ///              3) void issue(iter it)      - that will be called when the command is
    ///                                            detected by the parser in the input.
    ///                                            iter is defined as:
    ///                                               using iter = std::string::const_iterator;
    ///                                            it points to the first character in the argument. 
    template < typename Command >
    class UnaryCommandParser {
    public:

	explicit
	UnaryCommandParser(Command c = Command())
	    : rgx("^\\s*" + c.name() + "\\s+(" + c.pattern() + ")$")
	    , command(std::move(c))
	{ }

	bool accept(const std::string &s)
	{
	    std::smatch matches;

	    if (std::regex_match(s, matches, rgx)) {
		command.issue(matches[1].first);
		return true;

	    } else {
		return false;
	    }
	}
	
    private:

	std::regex rgx;
	
	Command command;
    };

    template < typename Command >
    auto unaryCommandParser(Command &&c)
    {
	using ValueType = typename std::decay<Command>::type;
	return UnaryCommandParser<ValueType>(std::forward<Command>(c));
    }
    
    /// @brief adapts a Nullary (with zero args) Command object to be included in a Case parser.
    ///        This parses a command in the form of "<command-name>".
    ///        You need to provide a copy or move-constructible type with the member functions:
    ///              1) std::string name()       - gives the name of the command
    ///
    ///              2) void issue()             - that will be called when the command is
    ///                                            detected by the parser in the input.
    template < typename Command >
    class CommandParser {
    public:
	
	explicit
	CommandParser(Command c = Command())
	    : rgx("^\\s*" + c.name() + "\\s*$")
	    , command(std::move(c))
	{ }

	bool accept(const std::string &s)
	{
	    std::smatch matches;

	    if (std::regex_match(s, matches, rgx)) {
		command.issue();
		return true;

	    } else {
		return false;
	    }
	}
	
    private:

	std::regex rgx;
	
	Command command;
    };

    template < typename Command >
    auto commandParser(Command &&c)
    {
	using ValueType = typename std::decay<Command>::type;
	return CommandParser<ValueType>(std::forward<Command>(c));
    }

    /// @brief adapts a Nullary (with zero args) Command object to be included in a Case parser.
    ///        This parses a command in the form of "<regex-pattern>" and sends the string that
    ///        has matched it back to the underlying command object.
    ///        You need to provide a copy or move-constructible type with the member functions:
    ///              1) std::string pattern()               - regular expression to match the strings
    ///
    ///              2) void issue(std::string)             - that will be called when the command is
    ///                                                       detected by the parser in the input, passing
    ///                                                       the matched string as an argument.
    template < typename Command >
    class GlobCommandParser {
    public:
	
	explicit
	GlobCommandParser(Command c = Command())
	    : rgx("^\\s*" + c.pattern() + "\\s*$")
	    , command(std::move(c))
	{ }

	bool accept(const std::string &s)
	{
	    std::smatch matches;

	    if (std::regex_match(s, matches, rgx)) {
		command.issue(s);
		return true;

	    } else {
		return false;
	    }
	}
	
    private:

	std::regex rgx;
	
	Command command;
    };

    template < typename Command >
    auto globCommandParser(Command &&c)
    {
	using ValueType = typename std::decay<Command>::type;
	return GlobCommandParser<ValueType>(std::forward<Command>(c));
    }
    
    /// @brief standard exit command, matches "exit" as the pattern that will end parsing.
    class ExitCommand {
    public:
	
	std::string name() const { return "exit"; }

	void issue()
	{
	    // do nothing, just let the parser exit
	}
    };

    inline auto standardExitParser()
    {
	return commandParser(ExitCommand{});
    }
}

#endif

