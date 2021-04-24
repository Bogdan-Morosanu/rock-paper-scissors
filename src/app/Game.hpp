#ifndef APP_ROUND_BUILDER
#define APP_ROUND_BUILDER

#include <iostream>
#include <array>

#include "game/GameHistory.hpp"
#include "MoveCommandParsers.hpp"

namespace app
{
    /// @brief class builds game rounds from user and ai inputs,
    ///        sending them to the rps game logic classes to get results
    class Game {
    public:

	Game(std::string playerOne, std::string playerTwo)
	    : turnComplete{true}
	    , prev{}
	    , mPlayerNames{ std::move(playerOne), std::move(playerTwo) }
	    , mHistory(rps::PlayerId{0u}, rps::PlayerId{1u})
	{ }
	
	void registerPlayerMove(rps::Move move)
	{
	    turnComplete = !turnComplete;

	    if (turnComplete) {
		mHistory.add(prev, move);
		this->streamResult(std::cout);
		
	    } else {
		prev = move;
	    }
	}

	rps::GameResult result() { return mHistory.result(); }

	void streamResult(std::ostream &out)
	{
	    auto gameResult = this->result();
	    out << "Game Score:\n"
		<< mPlayerNames[0] << " - " << gameResult.left.score << "\n"
		<< mPlayerNames[1] << " - " << gameResult.right.score << std::endl;
	}
	
    private:

	bool turnComplete;

	rps::Move prev;

	std::array<std::string, 2u> mPlayerNames;
		
	rps::GameHistory mHistory;
    };
}

#endif
