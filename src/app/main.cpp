#include <iostream>

#include "parser/Parser.hpp"
#include "parser/EchoCommand.hpp"
#include "app/MoveCommandParsers.hpp"

int main(int argc, char **argv)
{
    psr::Parser parser;

    parser.pushBack(psr::UnaryCommandParser<psr::EchoCommand>());
    parser.pushBack(psr::CommandParser<app::RockCommand>());
    parser.pushBack(psr::CommandParser<app::PaperCommand>());
    parser.pushBack(psr::CommandParser<app::ScissorsCommand>());
    
    parser.parseStream(std::cin, std::cerr);

    return 0;
}
