#include <iostream>

#include "parser/Parser.hpp"
#include "parser/EchoCommand.hpp"

int main(int argc, char **argv)
{
    psr::Parser parser;

    parser.pushBack(psr::UnaryCommandParser<psr::EchoCommand>());

    parser.parseStream(std::cin, std::cerr);
}
