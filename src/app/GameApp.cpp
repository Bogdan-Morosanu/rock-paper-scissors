#include "GameApp.hpp"

#include "app/prompt.hpp"

#include <string>

namespace
{
    std::string toString(rps::Move move)
    {
	switch (move) {
	case rps::Move::ROCK:
	    return "rock";
	    
	case rps::Move::PAPER:
	    return "paper";
	    
	case rps::Move::SCISSORS: default: // default: for compiler warnings
	    return "scissors";
	}
	    
    }
}

namespace app
{
    bool GameApp::hasAi() const
    {
	return mAi.isValid();
    }

    std::uint32_t GameApp::roundsLeft() const
    {
	return mNrRounds;
    }
    
    void GameApp::registerPlayerMove(rps::Move move)
    {
	if (!mAi.isValid()) {
	    throw std::logic_error("GameApp::registerPlayerMove ai oponent not generated yet!");
	}

	if (mNrRounds == 0u) {
	    throw std::logic_error("GameApp::registerPlayerMove the game is over!");
	}

	mNrRounds--;
	
	rps::Move aiMove = mAi.value().nextMove();

	std::cout << mHumanName << " chose " << toString(move) << "\n"
		  << mAi.value().name() << " chose " << toString(aiMove) << "\n";

	switch (rps::roundResult(move, aiMove)) {
	case rps::RoundResult::WIN_LEFT:
	    std::cout << mHumanName << " won!\n" << std::endl;
	    break;
		
	case rps::RoundResult::DRAW:
	    std::cout << "draw!\n" << std::endl;
	    break;
		
	case rps::RoundResult::WIN_RIGHT:
	    std::cout << mAi.value().name() << " won!\n" << std::endl;
	    break;
	}
	
	mHistory.add(move, aiMove);

	mAi.value().perceiveAdversaryMove(move);

	streamResult(std::cout);
    }

    void GameApp::setAi(ai::Strategy::StrategyType strategy)
    {
	auto stratToString = [](ai::Strategy::StrategyType strat)
	                     {
				 switch (strat) {
				 case ai::Strategy::CYBER_CHICKEN:
				     return "Cyber Chicken";
				     
				 case ai::Strategy::ELECTRIC_ELEPHANT:
				     return "Electric Elephant";
				     
				 case ai::Strategy::SPACE_SQUID: default: // default for compiler warning
				     return "Space Squid";				     
				 }
	                     };
	
	mAi = app::AiPlayer(stratToString(strategy), strategy);
    }

    void GameApp::setNrRounds(std::uint32_t nrRounds)
    {
	mNrRounds = nrRounds;
	std::cout << "Number of rounds set to " << std::to_string(nrRounds) << std::endl;
    }
    
    void GameApp::printGameIntro() const
    {
	std::cout << "The year is 3021. While running a routine transport mission in the gamma quadrant of our galaxy,\n"
	          << "your vessel was successfully boarded by space pirates. Now with all the treasure stowed away and\n"
	          << "you safely tied up, the crew stands in front of you expectantly.\n\n"
	          << "From time immemorial, space pirates have been known to follow the space pirate code section 127.1.0.42,\n"
                  << "which states that prisoners captured during boarding have the right to a game of rock-paper-scissors (RPS)\n"
                  << "to define their fate. You understand you can play a game of RPS against one of the crew memebers of\n"
		  << "your choice. After a number of rounds of your chosing, you must beat your oponent to keep your life.\n" 
		  << "A draw or a loss against the pirate will lead to your untimely demise.\n\n"
		  << "Standing before you, a Cyber Chicken, an Electric Elephant and a Space Squid.\n"
		  << "Please select your oponent:" << std::endl;

	displayPrompt();
    }

    void GameApp::printEndGameResult() const
    {
	if (roundsLeft() > 0u) {
	    // the user has quit via the exit command
	    std::cout << "As you signal your intention to forfeit the game, the pirates efficiently\n"
		      << "move you to a vac chamber and hit the EJECT button.\n\n"
		      << "Maybe you still had a chance, but you'll never know."
		      << std::endl;
	} else {

	    auto gameResult = result();

	    auto humanScore = gameResult.left.score;
	    auto aiScore = gameResult.right.score;

	    if (humanScore < aiScore) {
		std::cout << "With little regard to your protests, the pirates efficiently\n"
			  << "move you to a vac chamber and hit the EJECT button.\n\n"
		          << "As you drift into space without any life support, you spend a moment and reflect.\n"
			  << "How could you lose to a creature with no hands at a game of rock-paper-scissors?"
			  << std::endl;

	    } else if (humanScore == aiScore) {
		std::cout << "After a short routine check of subsection 127.1.0.42:194,\n"
			  << "the pirates determine your life is indeed forfeit on a draw result.\n"
			  << "With little regard to your protests, the pirates efficiently\n"
			  << "move you to a vac chamber and hit the EJECT button.\n\n"
		          << "As you drift into space without any life support, you spend a moment and reflect.\n"
			  << "How could you fail to beat a creature with no hands at a game of rock-paper-scissors?"
			  << std::endl;
	    } else {
		std::cout << "Acknowledging your win as a matter of fact, the pirates immediately sedate you.\n"
		          << "You wake up in what seems to be a back alley of some obscure space port.\n"
			  << "You're shaken, confused and broke; but you live to tell the tale!\n"
		          << std::endl;
	    }
	}
    }
    
    rps::GameResult GameApp::result() const
    {
	return mHistory.result();
    }

    void GameApp::streamResult(std::ostream &out)
    {
	if (!mAi.isValid()) {
	    throw std::logic_error("GameApp::streamResult ai oponent not generated yet!");
	}

	auto gameResult = this->result();
	out << "Game Score:\n"
	    << mHumanName << " - " << gameResult.left.score << "\n"
	    << mAi.value().name() << " - " << gameResult.right.score << "\n"
	    << "Rounds left: " << this->mNrRounds << std::endl;
    }

}
