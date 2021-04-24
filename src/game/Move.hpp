#ifndef GAME_MOVE
#define GAME_MOVE

#include "Player.hpp"

namespace rps
{
    struct Move {

	enum MoveType { ROCK, PAPER, SCISSORS };
	
	PlayerId player;
	
	MoveType moveType;
    };


    /// represents the result of playing one round of rock-paper-scissors
    struct RoundResult {
	enum RoundResultType { WIN, DRAW };

	RoundResultType resultType;

	PlayerId winner;
    };
    
    RoundResult result(Move left, Move right);
}

#endif
