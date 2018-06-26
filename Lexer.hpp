//
// Created by aloha on 6/14/18.
//

#ifndef AVM_LEXER_HPP
#define AVM_LEXER_HPP

#include <iostream>
#include <fstream>
#include <list>
#include "IOperand.hpp"

//check each case
enum tokenType{
    PUSH,
    POP,
    DUMP,
    ASSERT,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    PRINT,
    EXIT,
    COMMENT,
    INT8,
    INT16,
    INT32,
    FLOAT,
    DOUBLE,
};

struct Token {
    tokenType       _type;
    std::string     _value;
};

class Lexer {
public:
    Lexer(int ac, char **av);
    Lexer(const Lexer&);
    ~Lexer();

    Lexer&operator=(const Lexer&);

    void start();
    void eachLine(std::string &str);
    Token isInst(int &cnt, std::string &str, std::istringstream &iss);
    Token isValue(int &cnt, std::string &str);

    std::list<Token>& getTokens();

private:
    bool                _isFile = false;
    bool                _isInput = false;
    std::list<Token>   _tokens;
    std::ifstream       _ifs;
};


#endif //AVM_LEXER_HPP
