#ifndef APP_AI_PLAYER
#define APP_AI_PLAYER

#include "ai/Strategy.hpp"

namespace app
{
    class AiPlayer {
    public:

	explicit
	AiPlayer(std::string name, ai::Strategy::StrategyType strategy)
	    : mName(std::move(name))
	    , mStrategy(strategy)
	{ }
	
	const std::string &name() const { return mName; }

	rps::Move nextMove() const { return mStrategy.nextMove(); }

	void perceiveAdversaryMove(rps::Move move) { mStrategy.perceiveAdversaryMove(move); }

    private:
	
	std::string mName;

	ai::Strategy mStrategy;
    };
}

#endif
