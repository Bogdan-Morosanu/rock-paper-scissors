#ifndef APP_GAME_SELECT_COMMAND_PARSERS
#define APP_GAME_SELECT_COMMAND_PARSERS

#include <iostream>
#include <string>

#include "app/prompt.hpp"

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
		std::cout << "Tilting its head at an angle and staring blankly into your soul,\n"
		          << "the Cyber Chicken is ready for battle! Select the number of rounds:"
		          << std::endl;
		
		mGame->setAi(ai::Strategy::CYBER_CHICKEN);

	    } else {
		std::cout << "the oponent has already been selected, please select the number of rounds to play!" << std::endl;
	    }

	    displayPrompt();
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
		std::cout << "The Electric Elephant slowly moves to face you. Calculated and\n"
		          << "calm, he seems to never forget anything. Select the number of rounds"
			  << std::endl;

		mGame->setAi(ai::Strategy::ELECTRIC_ELEPHANT);

	    } else {
		std::cout << "the oponent has already been selected, please select the number of rounds to play!" << std::endl;
	    }

	    displayPrompt();
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
		std::cout << "Squirming with frantic excitement, the Space Squid seems\n"
		          << "excited to figure out your strategy. Select the number of rounds:"
		          << std::endl;
		
		mGame->setAi(ai::Strategy::SPACE_SQUID);
		
	    } else {
		std::cout << "the oponent has already been selected, please select the number of rounds to play!" << std::endl;
	    }

	    displayPrompt();
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
	    return "[+-]?\\d+\\.?\\d*";
	}

	void issue(const std::string &str) const
	{
	    auto annoyedMessage = []()
	                          {
			               std::cout << "Annoyed with your unreasonable number of rounds, the pirates\n"
		                                 << "have decided you will play SEVEN rounds of RPS.\n"
		                                 << "No more, no less!\n"; 
				  };

	    std::uint32_t rounds;

	    try {
		std::int32_t tentativeRounds = std::stoi(str);
		if (tentativeRounds < 1 || tentativeRounds > 42) {
		    annoyedMessage();
		    rounds = 7u;
		    
		} else {
		    rounds = static_cast<std::uint32_t>(tentativeRounds);
		}   
		
	    } catch(...) {
		annoyedMessage();
		rounds = 7u;
	    }
	    
	    mGame->setNrRounds(rounds);

	    std::cout << "Make your first move:\n";
	    displayPrompt();
	}
 
    private:
	// a pointer becase we need this class to support copy/move/swap
	app::GameApp *mGame;
    };
}

#endif