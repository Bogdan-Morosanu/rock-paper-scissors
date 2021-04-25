#include <iostream>

#include "parser/Parser.hpp"
#include "parser/EchoCommand.hpp"
#include "app/MoveCommandParsers.hpp"
#include "app/GameSelectCommandParsers.hpp"

int main(int argc, char **argv)
{
    app::GameApp game;

    game.printGameIntro();

    // select opponent and number of rounds from input
    psr::Parser pickOponentParser;
    pickOponentParser.pushBack(psr::commandParser(app::PickCyberChickenCommand{game}));
    pickOponentParser.pushBack(psr::commandParser(app::PickElectricElephantCommand{game}));
    pickOponentParser.pushBack(psr::commandParser(app::PickSpaceSquidCommand{game}));
    pickOponentParser.setExitParser(psr::globCommandParser(app::RoundNumberCommand{game}));
    pickOponentParser.setPromptCallback([]() { app::displayPrompt(); });
    pickOponentParser.parseStream(std::cin, std::cerr);
    
    // now grab rps commands
    psr::Parser gameRoundParser;
    gameRoundParser.pushBack(psr::commandParser(app::RockCommand{game}));
    gameRoundParser.pushBack(psr::commandParser(app::PaperCommand{game}));
    gameRoundParser.pushBack(psr::commandParser(app::ScissorsCommand{game}));
    gameRoundParser.setExitCallback([&game]() { return game.roundsLeft() == 0u; });
    gameRoundParser.setPromptCallback([]() { app::displayPrompt(); });
    
    gameRoundParser.parseStream(std::cin, std::cerr);

    game.printEndGameResult();
    
    return 0;
}
