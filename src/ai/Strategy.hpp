#ifndef AI_STRATEGY
#define AI_STRATEGY

#include <cstdlib>
#include <ctime>
#include <memory>

#include "game/Move.hpp"

namespace ai
{
    namespace detail
    {
	class StrategyImpl;
    }
    
    class Strategy {
    public:

	enum StrategyType { CYBER_CHICKEN, SPACE_SQUID, ELECTRIC_ELEPHANT, SCADA_SYSTEM };

	explicit
	Strategy(StrategyType type = CYBER_CHICKEN);

	Strategy(Strategy &&);

	Strategy & operator = (Strategy &&);
	
	/// inform the ai strategy of the newest move our adversary has made
	void perceiveAdversaryMove(rps::Move move);

	/// request the next move our strategy will play against our adversary
	rps::Move nextMove() const;

	~Strategy();
	
    private:

	std::unique_ptr<detail::StrategyImpl> mImpl;
    };
}

#endif
