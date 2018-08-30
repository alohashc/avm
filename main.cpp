#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"

int main(int ac, char **av) {
    Lexer lexer(ac, av);
    lexer.start();

    Parser parser(lexer.getTokens());
    parser.start();

    return 0;
}