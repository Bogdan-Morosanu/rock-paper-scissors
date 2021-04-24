#ifndef GAME_GAME_HISTORY
#define GAME_GAME_HISTORY

#include "Player.hpp"
#include "Move.hpp"


namespace rps
{
    struct GameResult {

	struct PlayerResult {

	    PlayerId player;
	    
	    std::uint32_t score = 0u;
	};

	PlayerResult left;

	PlayerResult right;
    };

    /// holds the score and history of moves from a game played between two players
    class GameHistory {
    public:

	struct Round {

	    Move left;

	    Move right;
	};

	GameHistory(PlayerId leftId, PlayerId rightId)
	    : mResult({leftId, 0u}, {rightId, 0u})
	    , mRounds()
	{ }
	
	void add(Move left, Move right)
	{
	    mRounds.push_back({left, right});

	    auto roundResult = rps::roundResult(left, right);

	    switch (roundResult) {
	    case rps::RoundResult::WIN_LEFT:
		mResult.left.score++;
		break;

	    case rps::RoundResult::DRAW:
		break;

	    case rps::RoundResult::WIN_RIGHT:
		mResult.right.score++;
		break;
	    }
	}

	const Round& getRound(std::uint32_t i) const { return mRounds[i]; };

	const GameResult& getResult() const { return mResult };
	
    private:

	GameResult mResult;

	std::vector<Round> mRounds;
    };
}

#endif
