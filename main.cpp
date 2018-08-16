#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "AvmExcept.hpp"

int main(int ac, char **av) {
    Lexer lexer(ac, av);
    lexer.start();

    try {
        Parser parser(lexer.getTokens());
        parser.start();
    }
    catch (AvmExcept &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}