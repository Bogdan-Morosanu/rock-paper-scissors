#ifndef GAME_GAME_HISTORY
#define GAME_GAME_HISTORY

#include "Player.hpp"
#include "Move.hpp"


namespace rps
{
    struct GameResult {

	struct PlayerResult {
	    PlayerId player;
	    std::int32_t score;
	};

	PlayerResult left;

	PlayerResult right;
    };


    /// holds the history of moves from a game played between two players
    class GameHistory {
    public:

	struct Round {
	    Move left;
	    Move right;
	};

	void add(Move left, Move right);

	Round 
	
    private:

	std::vector<Round> mRounds;
    };
}

#endif
