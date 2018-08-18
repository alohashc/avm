//
// Created by aloha on 6/14/18.
//

#include "Parser.hpp"
#include <regex>

Parser::Parser(std::list<Token> &tokens) : _tokens(tokens){
    _instr[PUSH] = &Parser::push;
    _instr[POP] = &Parser::pop;
    _instr[ASSERT] = &Parser::assert;
    _instr[ADD] = &Parser::add;
    _instr[SUB] = &Parser::sub;
    _instr[MUL] = &Parser::mul;
    _instr[DIV] = &Parser::div;
    _instr[MOD] = &Parser::mod;
    _instr[PRINT] = &Parser::print;
    _instr[DUMP] = &Parser::dump;
    _instr[EXIT] = &Parser::exit;
}

Parser::~Parser() {}

Parser::Parser(const Parser &src) {
    if (!src._tokens.empty())
        *this = src;
}

Parser& Parser::operator=(const Parser &rhs) {
    this->_tokens = rhs._tokens;
    this->_factory = rhs._factory;
    this->_instr = rhs._instr;
    this->_stack = rhs._stack;
    return *this;
}

void Parser::start() {
    std::string tmp;
    bool isExit =  false;

    for (auto &_token : _tokens) {
        if (_token._type > COMMENT) {
            tmp = _token._value;
            tmp.resize(tmp.size() - 1);
            size_t found = tmp.find('(') + 1;
            _token._value = tmp.substr(found);
        }
    }
    for (auto it = _tokens.begin(); it != _tokens.end(); ++it) {
        if (it->_value == "exit")
            isExit = true;
        void (Parser::*func)(std::list<Token>::iterator& it);
        func = _instr.at(it->_type);
        try {
            (this->*func)(it);
        }
        catch (AvmExcept &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    if (!isExit)
        throw AvmExcept("ERROR: exit instruction not found");
}

void Parser::push(std::list<Token>::iterator &it) {
    auto next = ++it;
    _stack.push_front(_factory.createOperand(static_cast<eOperandType>(next->_type - INT8), next->_value));
}

void Parser::pop(std::list<Token>::iterator &it) {
    (void)it;
    if (_stack.empty())
        throw AvmExcept("ERROR: stack is empty");
    _stack.pop_front();
}

void Parser::assert(std::list<Token>::iterator &it) {
    auto next = ++it;
    if (_stack.empty())
        throw AvmExcept("ERROR: stack is empty");
    const IOperand* first = *(_stack.begin());
    if (next->_value != first->toString())
        throw AvmExcept("ASSERT ERROR: different values");
    if (next->_type - INT8 != first->getType())
        throw AvmExcept("ASSERT ERROR: different values");
}

void Parser::dump(std::list<Token>::iterator &it) {
    (void)it;
    if (_stack.empty())
        throw AvmExcept("ERROR: stack is empty");
    for (auto &iter : _stack)
        std::cout << iter->toString() << std::endl;
}

void Parser::add(std::list<Token>::iterator &it) {
    (void)it;
    if (_stack.size() < 2)
        throw AvmExcept("ERROR: less than 2 elements");
    const IOperand* first = *(_stack.begin());
    _stack.pop_front();
    const IOperand* second = *(_stack.begin());
    _stack.pop_front();
    _stack.push_front(*first + *second);
    delete first;
    delete second;
}

void Parser::mul(std::list<Token>::iterator &it) {
    (void)it;
    if (_stack.size() < 2)
        throw AvmExcept("ERROR: less than 2 elements");
    const IOperand* first = *(_stack.begin());
    _stack.pop_front();
    const IOperand* second = *(_stack.begin());
    _stack.pop_front();
    _stack.push_front(*first * *second);
    delete first;
    delete second;
}

void Parser::sub(std::list<Token>::iterator &it) {
    (void)it;
    if (_stack.size() < 2)
        throw AvmExcept("ERROR: less than 2 elements");
    const IOperand* first = *(_stack.begin());
    _stack.pop_front();
    const IOperand* second = *(_stack.begin());
    _stack.pop_front();
    _stack.push_front(*first - *second);
    delete first;
    delete second;
}

void Parser::div(std::list<Token>::iterator &it) {
    (void)it;
    if (_stack.size() < 2)
        throw AvmExcept("ERROR: less than 2 elements");
    const IOperand* first = *(_stack.begin());
    _stack.pop_front();
    const IOperand* second = *(_stack.begin());
    if (first->toString() == "0")
        throw AvmExcept("ERROR: division on 0");
    _stack.pop_front();
    _stack.push_front(*second / *first);
    delete first;
    delete second;
}

void Parser::mod(std::list<Token>::iterator &it) {
    (void)it;
    if (_stack.size() < 2)
        throw AvmExcept("ERROR: less than 2 elements");
    const IOperand* first = *(_stack.begin());
    _stack.pop_front();
    const IOperand* second = *(_stack.begin());
    if (first->toString() == "0")
        throw AvmExcept("ERROR: division on 0");
    _stack.pop_front();
    _stack.push_front(*second % *first);
    delete first;
    delete second;
}

void Parser::print(std::list<Token>::iterator &it) {
    (void)it;
    if (_stack.empty())
        throw AvmExcept("Print instruction on empty stack");
    const IOperand* first = *(_stack.begin());
    if (first->getType() != Int8)
        throw AvmExcept("Print instruction on no 8-bit integer");
    std::cout << static_cast<char>(std::stoi(first->toString())) << std::endl;
}

void Parser::exit(std::list<Token>::iterator &it) {
    (void)it;
    std::exit(0);
}