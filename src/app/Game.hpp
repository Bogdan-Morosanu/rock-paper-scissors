#ifndef APP_ROUND_BUILDER
#define APP_ROUND_BUILDER

#include "game/GameHistory.hpp"
#include "MoveCommandParsers.hpp"

namespace app
{
    /// @brief class builds game rounds from user and ai inputs,
    ///        sending them to the rps game logic classes to get results
    class Game {
    public:

	void registerPlayerMove(rps::Move move)
	{
	    turnComplete = !turnComplete;

	    if (turnComplete) {
		mHistory.add(prev, move);

	    } else {
		prev = move;
	    }
	}

	rps::GameResult result() { return mHistory.result(); }
	
    private:

	bool turnComplete = true;

	rps::Move prev;
	
	rps::GameHistory mHistory;
    };
}

#endif
