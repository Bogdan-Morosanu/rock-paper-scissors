#include "Player.hpp"
#include "Move.hpp"

#include <stdexcept>

namespace rps
{
    RoundResult roundResult(Move left, Move right)
    {
	switch(left) {
	case Move::ROCK:
	    switch(right) {
	    case Move::ROCK:
		return RoundResult::DRAW;

	    case Move::PAPER:
		return RoundResult::WIN_RIGHT;

	    case Move::SCISSORS:
		return RoundResult::WIN_LEFT;
	    }
	    
	case Move::PAPER:
	    switch(right) {
	    case Move::ROCK:
		return RoundResult::WIN_LEFT;
		
	    case Move::PAPER:
		return RoundResult::DRAW;
		
	    case Move::SCISSORS:
		return RoundResult::WIN_RIGHT;
	    }

	case Move::SCISSORS:
	    switch(right) {
	    case Move::ROCK:
		return RoundResult::WIN_RIGHT;
		
	    case Move::PAPER:
		return RoundResult::WIN_LEFT;
		
	    case Move::SCISSORS:
		return RoundResult::DRAW;
	    }

	default:
	    return {}; // to please compiler warnings
	}
    }
}
