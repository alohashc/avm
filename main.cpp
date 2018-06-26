#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "AvmExcept.hpp"

// check exception
// check includes

int main(int ac, char **av) {
    try {
        Lexer lexer(ac, av);
        lexer.start();

        Parser parser(lexer.getTokens());
        parser.start();
    }
    catch (AvmExcept &e) {
        std::cerr <<  << e.what() <<  << std::endl;
    }
    return 0;
}