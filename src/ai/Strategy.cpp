#include "Strategy.hpp"

#include "ai/sampling.hpp"

#include <ctime>
#include <stdexcept>
#include <array>

namespace
{
    void srand()
    {
	std::srand(static_cast<unsigned>(std::time(0)));
    }
}

namespace ai
{

namespace detail
{
    class StrategyImpl {
    public:

	virtual rps::Move nextMove() const = 0;
	
	virtual void perceiveAdversaryMove(rps::Move move) = 0;
	
	virtual ~StrategyImpl() = default;
    };

    class CyberChickenStrategy final : public StrategyImpl {
    public:

	CyberChickenStrategy()
	{
	    srand();
	}

	rps::Move nextMove() const override
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

	void perceiveAdversaryMove(rps::Move) override
	{
	    // the chicken does not take the player's moves into account
	}
    };

    class ElectricElephantStrategy final : public StrategyImpl {
    public:

	ElectricElephantStrategy()
	    : mWeight(0.5) // original distribution has the weight of 0.5 moves
	    , mMoveDist{1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0}
	{
	    srand();
	}

	rps::Move nextMove() const override
	{
	    return sample(mMoveDist);
	}

	void perceiveAdversaryMove(rps::Move move) override
	{
	    mMoveDist[0] *= mWeight;
	    mMoveDist[1] *= mWeight;
	    mMoveDist[2] *= mWeight;
	    
	    switch (move) {
	    case rps::Move::ROCK:
		// paper beats rock
		mMoveDist[1] += 1.0;
		break;

	    case rps::Move::PAPER:
		// scissors beats paper
		mMoveDist[2] += 1.0;
		break;

	    case rps::Move::SCISSORS:
		// rock beats scissors
		mMoveDist[0] += 1.0;
		break;
	    }

	    // each observation has weight = 1.0
	    mMoveDist[0] /= (mWeight + 1.0);
	    mMoveDist[1] /= (mWeight + 1.0);
	    mMoveDist[2] /= (mWeight + 1.0);

	    mWeight += 1.0;
	}

    private:

	/// total weight of all observations and prior in the model
	double mWeight;

	/// distribution of observations combined with the prior
	std::array<double, 3> mMoveDist;
    };

    class SpaceSquidStrategy final : public StrategyImpl {
    public:

	explicit
	SpaceSquidStrategy(double decay = 0.9)
	    : mDecay(decay)
	    , mMoveDist{1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0}
	{
	    if (0.0 > decay || 1.0 < decay) {
		throw std::domain_error("SpaceSquidStrategy() - exponential decay factor must be in the [0.0, 1.0] interval!");
	    }
	    srand();
	}

	rps::Move nextMove() const override
	{
	    return sample(mMoveDist);
	}

	void perceiveAdversaryMove(rps::Move move) override
	{
	    // do an exponential decay of past observations
	    mMoveDist[0] *= mDecay;
	    mMoveDist[1] *= mDecay;
	    mMoveDist[2] *= mDecay;

	    // add new observation
	    switch (move) {
	    case rps::Move::ROCK:
		// paper beats rock
		mMoveDist[1] += (1.0 - mDecay);
		break;

	    case rps::Move::PAPER:
		// scissors beats paper
		mMoveDist[2] += (1.0 - mDecay);
		break;

	    case rps::Move::SCISSORS:
		// rock beats scissors
		mMoveDist[0] += (1.0 - mDecay);
		break;
	    }
	}

    private:

	/// weight to exponentially decay past observations and include new information (must be in [0.0, 1.0])
	double mDecay;

	/// distribution of observations combined with the prior
	std::array<double, 3> mMoveDist;
    };
}

    Strategy::Strategy(StrategyType strat)
	: mImpl()
    {
	switch (strat) {
	case CYBER_CHICKEN:
	    mImpl = std::make_unique<detail::CyberChickenStrategy>();
	    break;

	case ELECTRIC_ELEPHANT:
	    mImpl = std::make_unique<detail::ElectricElephantStrategy>();
	    break;

	case SPACE_SQUID: default: // TODO implement for SCADA too
	    mImpl = std::make_unique<detail::SpaceSquidStrategy>();
	    break;
	}
    }
    
    rps::Move Strategy::nextMove() const
    {
	return mImpl->nextMove();
    }

    void Strategy::perceiveAdversaryMove(rps::Move move)
    {
	mImpl->perceiveAdversaryMove(move);
    }

    Strategy::~Strategy() = default;
}
