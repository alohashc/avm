//
// Created by aloha on 6/14/18.
//

#ifndef AVM_PARSER_HPP
#define AVM_PARSER_HPP

#include "Lexer.hpp"
#include <stack>
#include "OperandFactory.hpp"

class Parser {
public:
    Parser(std::list<Token>&);
    ~Parser();

    Parser(const Parser&);
    Parser&operator=(const Parser&);

    void start();

    void    push(std::list<Token>::iterator& it);
    void    pop(std::list<Token>::iterator& it);
    void    dump(std::list<Token>::iterator& it);
    void    assert(std::list<Token>::iterator& it);
    void    add(std::list<Token>::iterator& it);
    void    sub(std::list<Token>::iterator& it);
    void    mul(std::list<Token>::iterator& it);
    void    div(std::list<Token>::iterator& it);
    void    mod(std::list<Token>::iterator& it);
    void    print(std::list<Token>::iterator& it);
    void    exit(std::list<Token>::iterator& it);
private:
    std::list<Token>   _tokens;
    OperandFactory      _factory;
    std::map<tokenType , void (Parser::*)(std::list<Token>::iterator& it)>    _instr;
    std::list<const IOperand*>                                               _stack;
};


#endif //AVM_PARSER_HPP
