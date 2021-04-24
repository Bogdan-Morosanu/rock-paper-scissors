#include "Player.hpp"
#include "Move.hpp"

#include <stdexcept>

namespace
{
    // helper functions for making a win or a draw result

    rps::RoundResult draw()
    {
	return { rps::RoundResult::DRAW, 0 };
    }

    rps::RoundResult win(rps::PlayerId id)
    {
	return { rps::RoundResult::WIN, id };
    }
}

namespace rps
{
    RoundResult result(Move left, Move right)
    {
	if (left.player == right.player) {
	    throw std::logic_error("rps::winner(Move, Move): corrupted player data, cannot play against the same player!");
	}

	switch(left.moveType) {
	case Move::ROCK:
	    switch(right.moveType) {
	    case Move::ROCK:
		return draw();

	    case Move::PAPER:
		return win(right.player);

	    case Move::SCISSORS:
		return win(left.player);
	    }
	    
	case Move::PAPER:
	    switch(right.moveType) {
	    case Move::ROCK:
		return win(left.player);
		
	    case Move::PAPER:
		return draw();
		
	    case Move::SCISSORS:
		return win(right.player);
	    }

	case Move::SCISSORS:
	    switch(right.moveType) {
	    case Move::ROCK:
		return win(right.player);
		
	    case Move::PAPER:
		return win(left.player);
		
	    case Move::SCISSORS:
		return draw();
	    }

	default:
	    return {}; // to please compiler warnings
	}
    }
}
