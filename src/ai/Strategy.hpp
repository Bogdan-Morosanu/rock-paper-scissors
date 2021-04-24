#ifndef AI_STRATEGY
#define AI_STRATEGY

#include <cstdlib>
#include <ctime>

#include "game/Move.hpp"

namespace ai
{

    class Strategy {
    public:

	Strategy()
	{
	    std::srand(static_cast<unsigned>(std::time(0)));
	}
	
	/// inform the ai strategy of the newest move our adversary has made
	void perceiveAdversaryMove(rps::Move move) { }

	/// request the next move our strategy will play against our adversary
	rps::Move nextMove() const
	{
	    switch(std::rand() % 3) {
	    case 0:
		return rps::Move::ROCK;
	    case 1:
		return rps::Move::PAPER;
	    case 2: default: // default for compiler warnings
		return rps::Move::SCISSORS;
	    }
	}

    private:
	
    };
}

#endif
