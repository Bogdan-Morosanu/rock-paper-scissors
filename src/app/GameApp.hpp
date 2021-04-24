#ifndef APP_GAME_APP
#define APP_GAME_APP

#include <iostream>
#include <array>

#include "game/GameHistory.hpp"
#include "app/AiPlayer.hpp"

namespace app
{
    /// @brief class builds game rounds from user and ai inputs,
    ///        sending them to the rps game logic classes to get results
    class GameApp {
    public:

	GameApp()
	    : mHumanName("You")
	    , mHistory(rps::PlayerId{0u}, rps::PlayerId{1u})
	    , mAi("Electric Elephant", ai::Strategy::ELECTRIC_ELEPHANT)
	{ }
	
	void registerPlayerMove(rps::Move move);
	
    private:

	rps::GameResult result();
	
	void streamResult(std::ostream &out);

	std::string mHumanName;
	
	rps::GameHistory mHistory;

	app::AiPlayer mAi;
    };
}

#endif
