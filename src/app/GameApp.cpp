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
	std::cout << "Welcome to space pirate RPS simulator!" << std::endl;
	std::cout << "Please select your oponent" << std::endl;
	displayPrompt();
    }

    void GameApp::printEndGameResult() const
    {
	std::cout << "Game over." << std::endl;
    }
    
    rps::GameResult GameApp::result()
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
