#ifndef PSR_PARSER
#define PSR_PARSER

#include <iostream>
#include <functional>

#include "Commands.hpp"

namespace psr {

    class Parser {
    public:

	Parser()
	    : cases()
	    , exitParser(std::make_unique<CaseModel<CommandParser<ExitCommand>>>(standardExitParser()))
	    , exitCallback([]() { return false; })
	    , printPrompt([](){ })
	{ }

	template < typename Case >
	void pushBack(Case&& c)
	{
	    using ValueType = typename std::decay<Case>::type;
	    cases.push_back(std::make_unique<CaseModel<ValueType>>(std::forward<Case>(c)));
	}

	template < typename ExitCase >
	void setExitParser(ExitCase &&ec)
	{
	    using ValueType = typename std::decay<ExitCase>::type;
            this->exitParser = std::make_unique<CaseModel<ValueType>>(std::forward<ExitCase>(ec));
	}

	void setExitCallback(std::function<bool(void)> ec)
	{
	    exitCallback = std::move(ec);
	}

	void setPromptCallback(std::function<void(void)> pc)
	{
	    printPrompt = std::move(pc);
	}
        
	/// parse input stream in and log parsing errors to err
	void parseStream(std::istream &in, std::ostream &err);
	
    private:

	// we use the runtime concept idiom to implement polymorphic behaviour in our parser.
	//
	// our users define their own types and we can add them to our composite without
	// requiring intrusive intervention like inheriting from some base class (which may be
	// undesirable).
	//
	// all our users need to do is provide *any* type with the given interface.
	//
	struct CaseConcept {

	    virtual bool accept(const std::string &str) = 0;

	    virtual ~CaseConcept() = default;
	};

	template < typename Case >
	struct CaseModel final : public CaseConcept {

	    CaseModel(Case &&cs)
	      : c(std::forward<Case>(cs))
	    { }
	    
	    bool accept(const std::string &str)
	    {
		return c.accept(str);
	    }

	    Case c;
	};

	std::vector<std::unique_ptr<CaseConcept>> cases;

	std::unique_ptr<CaseConcept> exitParser;

	std::function<bool(void)> exitCallback;

	std::function<void(void)> printPrompt;
    };
}

#endif
