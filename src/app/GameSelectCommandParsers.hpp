#ifndef APP_GAME_SELECT_COMMAND_PARSERS
#define APP_GAME_SELECT_COMMAND_PARSERS

#include <iostream>
#include <string>

namespace app
{
    class PickCyberChickenCommand {
    public:

	explicit
	PickCyberChickenCommand(GameApp &game)
	    : mGame(&game)
	{ }

	std::string name() const
	{
	    return "Cyber Chicken";
	}

	void issue() const
	{
	    if (!mGame->hasAi()) {
		mGame->setAi(ai::Strategy::CYBER_CHICKEN);

	    } else {
		std::cout << "the oponent has already been selected, please select the number of rounds to play!" << std::endl;
	    }
	}

    private:

	// a pointer becase we need this class to support copy/move/swap
	app::GameApp *mGame;
    };

    class PickElectricElephantCommand {
    public:

	explicit
	PickElectricElephantCommand(GameApp &game)
	    : mGame(&game)
	{ }

	std::string name() const
	{
	    return "Electric Elephant";
	}

	void issue() const
	{
	    if (!mGame->hasAi()) {
		mGame->setAi(ai::Strategy::ELECTRIC_ELEPHANT);

	    } else {
		std::cout << "the oponent has already been selected, please select the number of rounds to play!" << std::endl;
	    }
	}

    private:

	// a pointer becase we need this class to support copy/move/swap
	app::GameApp *mGame;
    };

    class PickSpaceSquidCommand {
    public:

	explicit
	PickSpaceSquidCommand(GameApp &game)
	    : mGame(&game)
	{ }

	std::string name() const
	{
	    return "Space Squid";
	}

	void issue() const
	{
	    if (!mGame->hasAi()) {
		mGame->setAi(ai::Strategy::SPACE_SQUID);
		
	    } else {
		std::cout << "the oponent has already been selected, please select the number of rounds to play!" << std::endl;
	    }
	}

    private:

	// a pointer becase we need this class to support copy/move/swap
	app::GameApp *mGame;
    };

    class RoundNumberCommand {
    public:

	explicit
	RoundNumberCommand(GameApp &game)
	    : mGame(&game)
	{ }
	
	std::string pattern() const
	{
	    return "(+|-)?\\d+\\.?\\d*";
	}

	void issue(const std::string &str) const
	{
	    auto annoyedMessage = []()
	                          {
			               std::cout << "annoyed with your unreasonable number of rounds,\n"
		                                 << "the pirates have decided you will play FIVE rounds of RPS.\n"
		                                 << "no more, no less!"
		                                 << std::endl;
				    };

	    std::uint32_t rounds;

	    try {
		std::int32_t tentativeRounds = std::stoi(str);
		if (tentativeRounds < 1 && tentativeRounds > 42) {
		    annoyedMessage();
		    rounds = 5u;
		    
		} else {
		    rounds = static_cast<std::uint32_t>(tentativeRounds);
		}   
		
	    } catch(...) {
		annoyedMessage();
		rounds = 5u;
	    }
	    
	    mGame->setNrRounds(rounds);
	}

    private:
	// a pointer becase we need this class to support copy/move/swap
	app::GameApp *mGame;
    };
}

#endif
