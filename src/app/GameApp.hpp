#ifndef APP_GAME_APP
#define APP_GAME_APP

#include <array>
#include <iostream>
#include <cstdint>

#include "game/GameHistory.hpp"
#include "app/AiPlayer.hpp"
#include "app/Optional.hpp"

namespace app
{
    /// @brief class builds game rounds from user and ai inputs,
    ///        sending them to the rps game logic classes to get results
    class GameApp {
    public:

	GameApp()
	    : mHumanName("You")
	    , mHistory(rps::PlayerId{0u}, rps::PlayerId{1u})
	    , mAi()
	{ }
	
	void registerPlayerMove(rps::Move move);

	void setAi(ai::Strategy::StrategyType strategy);

	void setNrRounds(std::uint32_t nrRounds);
	
	void printGameIntro() const;

	void printEndGameResult() const;
	
	bool hasAi() const;

	std::uint32_t roundsLeft() const;
	
    private:

	rps::GameResult result();
	
	void streamResult(std::ostream &out);

	std::string mHumanName;
	
	rps::GameHistory mHistory;

	std::uint32_t mNrRounds;
	
	app::Optional<app::AiPlayer> mAi;
    };
}

#endif
