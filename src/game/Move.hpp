#ifndef GAME_MOVE
#define GAME_MOVE

#include "Player.hpp"

namespace rps
{
    enum class Move { ROCK, PAPER, SCISSORS };

    /// represents the result of playing one round of rock-paper-scissors
    enum class RoundResult { WIN_LEFT, DRAW, WIN_RIGHT };
    
    RoundResult roundResult(Move left, Move right);
}

#endif
