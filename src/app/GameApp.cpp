#include "GameApp.hpp"

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

    void GameApp::registerPlayerMove(rps::Move move)
    {
	rps::Move aiMove = mAi.nextMove();

	std::cout << mHumanName << " chose " << toString(move) << "\n"
		  << mAi.name() << " chose " << toString(aiMove) << "\n";

	switch (rps::roundResult(move, aiMove)) {
	case rps::RoundResult::WIN_LEFT:
	    std::cout << mHumanName << " won!\n" << std::endl;
	    break;
		
	case rps::RoundResult::DRAW:
	    std::cout << "draw!\n" << std::endl;
	    break;
		
	case rps::RoundResult::WIN_RIGHT:
	    std::cout << mAi.name() << " won!\n" << std::endl;
	    break;
	}
	    
	mHistory.add(move, aiMove);

	mAi.perceiveAdversaryMove(move);

	streamResult(std::cout);
    }

    rps::GameResult GameApp::result()
    {
	return mHistory.result();
    }

    void GameApp::streamResult(std::ostream &out)
    {
	auto gameResult = this->result();
	out << "Game Score:\n"
	    << mHumanName << " - " << gameResult.left.score << "\n"
	    << mAi.name() << " - " << gameResult.right.score << std::endl;
    }

}
