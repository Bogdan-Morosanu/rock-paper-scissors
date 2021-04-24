#include <iostream>

#include "parser/Parser.hpp"
#include "parser/EchoCommand.hpp"
#include "app/MoveCommandParsers.hpp"

int main(int argc, char **argv)
{
    psr::Parser parser;
    app::Game game("Player1", "Player2");
    
    parser.pushBack(psr::unaryCommandParser(psr::EchoCommand{}));

    parser.pushBack(psr::commandParser(app::RockCommand{game}));
    parser.pushBack(psr::commandParser(app::PaperCommand{game}));
    parser.pushBack(psr::commandParser(app::ScissorsCommand{game}));
    
    parser.parseStream(std::cin, std::cerr);

    return 0;
}
